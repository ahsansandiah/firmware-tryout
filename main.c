#include <stdint.h>
#include <stdbool.h>

// Simple firmware skeleton for a car wash controller MCU.
// Focus: basic state machine, I/O placeholders, safety handling, periodic tasks.

typedef enum {
    STATE_IDLE = 0,
    STATE_READY,
    STATE_RUNNING,
    STATE_FAULT
} system_state_t;

typedef struct {
    bool estop_active;
    bool comms_ok;
    bool sensors_ok;
    uint16_t supply_mv;
} health_t;

static system_state_t state = STATE_IDLE;
static health_t health = {0};

// Hardware abstraction placeholders -----------------------------------------
static void hal_init(void) {
    // TODO: init clocks, GPIO, ADC, timers, UART/CAN, watchdog, NVIC, etc.
}

static void hal_feed_watchdog(void) {
    // TODO: feed hardware watchdog.
    (void)0;
}

static bool hal_estop_read(void) {
    // TODO: read E-stop input (active low/high per wiring).
    return false;
}

static bool hal_comms_alive(void) {
    // TODO: e.g., CAN/RS485 heartbeat from bay controller/PLC.
    return true;
}

static bool hal_sensors_healthy(void) {
    // TODO: validate sensor ranges (pressure/flow/level).
    return true;
}

static uint16_t hal_supply_voltage_mv(void) {
    // TODO: ADC read of supply rail (scaled to millivolts).
    return 24000;
}

static void hal_all_outputs_off(void) {
    // TODO: disable motors/relays safely.
}

static void hal_run_wash_step(void) {
    // TODO: execute one slice of the wash program (PWM, valves, timing).
}

static void hal_log_event(const char *msg) {
    (void)msg;
    // TODO: route to UART/flash log.
}

// Health monitoring ----------------------------------------------------------
static void update_health(void) {
    health.estop_active = hal_estop_read();
    health.comms_ok = hal_comms_alive();
    health.sensors_ok = hal_sensors_healthy();
    health.supply_mv = hal_supply_voltage_mv();
}

static bool health_faulted(void) {
    if (health.estop_active) return true;
    if (!health.comms_ok) return true;
    if (!health.sensors_ok) return true;
    if (health.supply_mv < 18000 || health.supply_mv > 30000) return true;
    return false;
}

// State machine --------------------------------------------------------------
static void enter_state(system_state_t next) {
    state = next;
    switch (state) {
        case STATE_IDLE:    hal_log_event("STATE_IDLE"); break;
        case STATE_READY:   hal_log_event("STATE_READY"); break;
        case STATE_RUNNING: hal_log_event("STATE_RUNNING"); break;
        case STATE_FAULT:   hal_log_event("STATE_FAULT"); break;
    }
}

static void state_step(void) {
    switch (state) {
        case STATE_IDLE:
            if (!health_faulted()) {
                enter_state(STATE_READY);
            }
            break;
        case STATE_READY:
            // TODO: check start command or vehicle detected.
            if (health_faulted()) {
                enter_state(STATE_FAULT);
            } else {
                enter_state(STATE_RUNNING);
            }
            break;
        case STATE_RUNNING:
            if (health_faulted()) {
                hal_all_outputs_off();
                enter_state(STATE_FAULT);
                break;
            }
            hal_run_wash_step();
            // TODO: exit criteria when program complete -> READY or IDLE.
            break;
        case STATE_FAULT:
            hal_all_outputs_off();
            // TODO: wait for operator reset + healthy status to recover.
            if (!health_faulted()) {
                enter_state(STATE_READY);
            }
            break;
    }
}

// Main loop -----------------------------------------------------------------
int main(void) {
    hal_init();
    enter_state(STATE_IDLE);

    while (1) {
        hal_feed_watchdog();
        update_health();
        state_step();
        // TODO: add periodic scheduling (tick/RTOS) and comms polling.
    }
}

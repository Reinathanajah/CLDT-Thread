#include "backhaul.h"

esp_err_t cldt_backhaul_init(const cldt_backhaul_config_t *config)
{
    (void)config;

    /*
     * IMPLEMENTATION TODO: validate credentials and callbacks without logging
     * secrets, initialize Wi-Fi station mode, wait for private-LAN readiness,
     * create MQTT client state, and register callbacks that only enqueue bounded
     * command or connection events. Do not start a measured run, publish a policy,
     * or start the HTTP server from init. Every partial resource needs a defined
     * cleanup path for a failed credential, Wi-Fi, or broker connection.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_backhaul_start(void)
{
    /*
     * IMPLEMENTATION TODO: start Wi-Fi and broker connections through an explicit
     * state machine, publish connection/health changes as traceable events, and
     * use bounded backoff outside any Thread, policy, or timing-critical lock.
     * A reconnect must never resurrect an expired policy or turn a retained broker
     * message into a command. The local guard remains safe while backhaul is down.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_backhaul_publish_observation(
    cldt_run_id_t run_id,
    cldt_node_id_t node_id,
    const uint8_t *payload,
    size_t payload_bytes)
{
    (void)run_id;
    (void)node_id;
    (void)payload;
    (void)payload_bytes;

    /*
     * IMPLEMENTATION TODO: validate run/node IDs and bounded payload size, add
     * immutable envelope metadata, publish observations at the selected QoS, and
     * make disconnected behavior explicit: either bounded drop with a trace event
     * or a bounded local queue with a recorded high-water mark. Never block a
     * Thread receive task on broker reconnect and never use retained observations
     * as current truth for a controller.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_backhaul_start_manifest_server(void)
{
    /*
     * IMPLEMENTATION TODO: bind only to the private experiment interface, cap
     * request/body size, accept a single complete manifest document into staging
     * storage, validate syntax and schema before acknowledgement, and pass only a
     * digest plus approved subset to supervisor. The HTTP handler may never alter
     * an active run. Reject credentials, command injection, and high-rate uploads.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_backhaul_stop(void)
{
    /*
     * IMPLEMENTATION TODO: stop accepting HTTP uploads first, make command
     * callbacks reject new policy input, signal the supervisor that backhaul is
     * leaving service, drain or account for only the bounded observation queue,
     * disconnect MQTT and Wi-Fi with bounded timeouts, and clear callback state.
     * The function must be safe after a partial init and must not overwrite run
     * evidence just because the network is unavailable.
     */
    return ESP_ERR_NOT_SUPPORTED;
}

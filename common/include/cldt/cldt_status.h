#ifndef CLDT_STATUS_H
#define CLDT_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Status values are stable public contracts. A caller records the exact status
 * at a trust, parsing, queue, or transport boundary; it must not convert an
 * error into success merely to keep a run moving. Platform adapters may map an
 * ESP-IDF or broker error to CLDT_ERR_IO, but semantic failures below remain
 * distinct so evidence can explain why a message or policy was rejected.
 */
typedef enum {
    CLDT_OK = 0,
    /* Caller or callee pointer/range/precondition was invalid. */
    CLDT_ERR_INVALID_ARGUMENT = -1,
    /* Bounded caller-owned storage, pool, queue, or encoder output was full. */
    CLDT_ERR_NO_SPACE = -2,
    /* Bytes or state violate the current protocol or data-structure contract. */
    CLDT_ERR_MALFORMED = -3,
    /* Frame version cannot be safely interpreted by this implementation. */
    CLDT_ERR_UNSUPPORTED_VERSION = -4,
    /* Required message authenticity verification failed. */
    CLDT_ERR_AUTHENTICATION = -5,
    /* A finite deadline or policy TTL elapsed before acceptable processing. */
    CLDT_ERR_EXPIRED = -6,
    /* A logical item or policy epoch has already been accepted. */
    CLDT_ERR_DUPLICATE = -7,
    /* A record or epoch is older than the accepted monotonic sequence. */
    CLDT_ERR_OUT_OF_ORDER = -8,
    /* A syntactically valid value exceeds a declared or compiled safety bound. */
    CLDT_ERR_OUT_OF_RANGE = -9,
    /* The operation conflicts with lifecycle or ownership state. */
    CLDT_ERR_WRONG_STATE = -10,
    /* Required attachment, calibration, or evidence is not yet available. */
    CLDT_ERR_NOT_READY = -11,
    /* An external file, socket, broker, or platform operation failed. */
    CLDT_ERR_IO = -12,
    /* A well-formed observation or command is older than its freshness rule. */
    CLDT_ERR_STALE = -13,
    /* A well-formed frame belongs to a run other than the active run. */
    CLDT_ERR_WRONG_RUN = -14,
    /* Intentional scaffold marker; it is never a valid experiment outcome. */
    CLDT_ERR_NOT_IMPLEMENTED = -127
} cldt_status_t;

#ifdef __cplusplus
}
#endif

#endif

#pragma once

/// Possible actions that can be performed on input objects
enum class ActionType {
    AS_IS, ///< Return object as-is
    AS_FLOAT, ///< Force as Python float
    AS_INT, ///< Force as Python int
    TRY_INT_IN_PYTHON, ///< Use Python int for conversion
    TRY_FLOAT_IN_PYTHON, ///< Use Python float for conversion
    TRY_FLOAT_THEN_FORCE_INT_IN_PYTHON, ///< Use Python float for conversion then force
                                        ///< to int
    TRY_FLOAT_THEN_COERCE_INT_IN_PYTHON, ///< Use Python float for conversion then make
                                         ///< int if int-like
    NAN_ACTION, ///< Return NaN
    INF_ACTION, ///< Return infinity
    NEG_NAN_ACTION, ///< Return negative NaN
    NEG_INF_ACTION, ///< Return negative infinity
    ERROR_INVALID_INT, ///< Raise invalid int exception
    ERROR_INVALID_FLOAT, ///< Raise invalid float exception
    ERROR_INVALID_BASE, ///< Raise invalid base exception
    ERROR_INFINITY_TO_INT, ///< Raise oveflow for infintity to int
    ERROR_NAN_TO_INT, ///< Raise NaN to int exception
    ERROR_BAD_TYPE_INT, ///< Raise invalid type for int
    ERROR_BAD_TYPE_FLOAT, ///< Raise invalid type for float
};

/// The types of data that Payload can store
enum class PayloadType {
    ACTION, ///< An ActionType enum value
    LONG, ///< A C-long
    DOUBLE, ///< A C-double
    DOUBLE_TO_LONG, ///< A C-double type that must be converted to long
};

/**
 * \brief Transfer data intended to be converted to Python objects
 *
 * Various functions can return different values (or errors) depending
 * on user parameters. This class uniformly stores all types for smoothest
 * transfer into "Python-land".
 */
class Payload {
public:
    /// Default construct - needed for use with Cython.
    Payload()
        : m_type(PayloadType::ACTION)
        , m_actval(ActionType::AS_IS)
    { }

    /// Construct the payload with an action.
    explicit Payload(const ActionType atype)
        : m_type(PayloadType::ACTION)
        , m_actval(atype)
    { }

    /// Construct the payload with a double.
    explicit Payload(const double val)
        : m_type(PayloadType::DOUBLE)
        , m_dval(val)
    { }

    /// Construct the payload with a double that needs to be be converted to an int.
    explicit Payload(const double val, const bool needs_int_conversion)
        : m_type(
            needs_int_conversion ? PayloadType::DOUBLE_TO_LONG : PayloadType::DOUBLE
        )
        , m_dval(val)
    { }

    /// Construct the payload with a long.
    explicit Payload(const long val)
        : m_type(PayloadType::LONG)
        , m_ival(val)
    { }

    // Copy, assignment, and destruct are defaults
    Payload(const Payload&) = default;
    Payload(Payload&&) = default;
    Payload& operator=(const Payload&) = default;
    ~Payload() = default;

    /// What type of payload is being carried?
    PayloadType payload_type() const { return m_type; }

    /// Return the Payload as an ActionType.
    ActionType get_action() const { return m_actval; }

    /// Return the Payload as a double.
    double to_double() const { return m_dval; }

    /// Return the Payload as a long.
    long to_long() const { return m_ival; }

private:
    /// Tracker of what type is being stored
    PayloadType m_type;

    /**
     * \brief All possible Payload types, occupying the same memory
     *
     * To minimize copy overhead, all possible Payload types are
     * placed in a union so that there is no wasted space. Only one
     * of these can be valid at a time.
     */
    union {
        /// The Payload as a long
        long m_ival;
        /// The Payload as a double
        double m_dval;
        /// The Payload as an ActionType
        ActionType m_actval;
    };
};

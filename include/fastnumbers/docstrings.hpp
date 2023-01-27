#pragma once

#include <Python.h>

PyDoc_STRVAR(fastnumbers__doc__, "Quickly convert strings to numbers.\n");

PyDoc_STRVAR(
    fast_real__doc__,
    "fast_real(x, default=None, raise_on_invalid=False, on_fail=None, nan=None, "
    "inf=None, coerce=True, allow_underscores=True)\n"
    "Quickly convert input to an `int` or `float` depending on value.\n"
    "\n"
    "Any input that is valid for the built-in `float` or `int` functions will\n"
    "be converted to either a `float` or `int`. An input of a single numeric\n"
    "unicode character is also valid. The return value is guaranteed\n"
    "to be of type `str`, `int`, or `float`.\n"
    "\n"
    "If the given input is a string and cannot be converted to a `float` or\n"
    "`int`, it will be returned as-is unless `default` or `raise_on_invalid`\n"
    "is given.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input : {str, float, int, long}\n"
    "    The input you wish to convert to a real number.\n"
    "default : optional\n"
    "    This value will be returned instead of the input\n"
    "    when the input cannot be converted. Has no effect if\n"
    "    *raise_on_invalid* is *True*.\n"
    "raise_on_invalid : bool, optional\n"
    "    If *True*, a `ValueError` will be raised if string input cannot be\n"
    "    converted to a `float` or `int`. If *False*, the string will be\n"
    "    returned as-is. The default is *False*.\n"
    "on_fail : callable, optional\n"
    "    If given and the *input* cannot be converted, the input will be\n"
    "    passed to the callable object and its return value will be returned.\n"
    "    The function expect only one positional argument.\n"
    "    For backwards-compatability, you may call this option `key` instead\n"
    "    of `on_fail`, but this is deprecated behavior.\n"
    "nan : optional\n"
    "    If the input value is NAN or can be parsed as NAN, return this\n"
    "    value instead of NAN.\n"
    "inf : optional\n"
    "    If the input value is INF or can be parsed as INF, return this\n"
    "    value instead of INF.\n"
    "coerce : bool, optional\n"
    "    If the input can be converted to an `int` without loss of precision\n"
    "    (even if the input was a `float` or float-containing `str`)\n"
    "    coerce to an *int* rather than returning a `float`.\n"
    "allow_underscores : bool, optional\n"
    "    Starting with Python 3.6, underscores are allowed in numeric literals\n"
    "    and in strings passed to `int` or `float` (see PEP 515 for details on\n"
    "    what is and is not allowed). You can disable that behavior by setting\n"
    "    this option to *False* - the default is *True*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "out : {str, float, int}\n"
    "    If the input could be converted to an `int`, the return type will be\n"
    "    `int`.\n"
    "    If the input could be converted to a `float` but not an `int`, the\n"
    "    return type will be `float`.  Otherwise, the input `str` will be\n"
    "    returned as-is (if `raise_on_invalid` is *False*) or whatever value\n"
    "    is assigned to `default` if `default` is not *None*.\n"
    "\n"
    "Raises\n"
    "------\n"
    "TypeError\n"
    "    If the input is not one of `str`, `float`, or `int`.\n"
    "ValueError\n"
    "    If `raise_on_invalid` is *True*, this will be raised if the input\n"
    "    string cannot be converted to a `float` or `int`.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "check_real\n"
    "real\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import fast_real\n"
    "    >>> fast_real('56')\n"
    "    56\n"
    "    >>> fast_real('56.0')\n"
    "    56\n"
    "    >>> fast_real('56.0', coerce=False)\n"
    "    56.0\n"
    "    >>> fast_real('56.07')\n"
    "    56.07\n"
    "    >>> fast_real('56.07 lb')\n"
    "    '56.07 lb'\n"
    "    >>> fast_real(56.07)\n"
    "    56.07\n"
    "    >>> fast_real(56.0)\n"
    "    56\n"
    "    >>> fast_real(56.0, coerce=False)\n"
    "    56.0\n"
    "    >>> fast_real(56)\n"
    "    56\n"
    "    >>> fast_real('invalid', default=50)\n"
    "    50\n"
    "    >>> fast_real('invalid', 50)  # 'default' is first optional positional arg\n"
    "    50\n"
    "    >>> fast_real('nan')\n"
    "    nan\n"
    "    >>> fast_real('nan', nan=0)\n"
    "    0\n"
    "    >>> fast_real('56.07', nan=0)\n"
    "    56.07\n"
    "    >>> fast_real('56.07 lb', raise_on_invalid=True) #doctest: "
    "+IGNORE_EXCEPTION_DETAIL\n"
    "    Traceback (most recent call last):\n"
    "      ...\n"
    "    ValueError: could not convert string to float: '56.07 lb'\n"
    "    >>> fast_real('invalid', on_fail=len)\n"
    "    7\n"
    "\n"
    "Notes\n"
    "-----\n"
    "It is roughly equivalent to (but much faster than)\n"
    "\n"
    "    >>> def py_fast_real(input, default=None, raise_on_invalid=False,\n"
    "    ...                  on_fail=None, nan=None, inf=None):\n"
    "    ...     import math\n"
    "    ...     try:\n"
    "    ...         a = float(input)\n"
    "    ...     except ValueError:\n"
    "    ...         if raise_on_invalid:\n"
    "    ...             raise\n"
    "    ...         elif on_fail is not None:\n"
    "    ...             return on_fail(input)\n"
    "    ...         elif default is not None:\n"
    "    ...             return default\n"
    "    ...         else:\n"
    "    ...             return input\n"
    "    ...     else:\n"
    "    ...         if nan is not None and math.isnan(a):\n"
    "    ...             return nan\n"
    "    ...         elif inf is not None and math.isinf(a):\n"
    "    ...             return inf\n"
    "    ...         else:\n"
    "    ...             return int(a) if a.is_integer() else a\n"
    "    ... \n"
    "\n"
);

PyDoc_STRVAR(
    fast_float__doc__,
    "fast_float(x, default=None, raise_on_invalid=False, on_fail=None, nan=None, "
    "inf=None, allow_underscores=True)\n"
    "Quickly convert input to a `float`.\n"
    "\n"
    "Any input that is valid for the built-in `float` function will\n"
    "be converted to a `float`. An input of a single numeric\n"
    "unicode character is also valid. The return value is guaranteed\n"
    "to be of type `str` or `float`.\n"
    "\n"
    "If the given input is a string and cannot be converted to a `float`\n"
    "it will be returned as-is unless `default` or `raise_on_invalid`\n"
    "is given.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input : {str, float, int, long}\n"
    "    The input you wish to convert to a `float`.\n"
    "default : optional\n"
    "    This value will be returned instead of the input\n"
    "    when the input cannot be converted. Has no effect if\n"
    "    *raise_on_invalid* is *True*.\n"
    "raise_on_invalid : bool, optional\n"
    "    If *True*, a `ValueError` will be raised if string input cannot be\n"
    "    converted to a `float`.  If *False*, the string will be\n"
    "    returned as-is.  The default is *False*.\n"
    "on_fail : callable, optional\n"
    "    If given and the *input* cannot be converted, the input will be\n"
    "    passed to the callable object and its return value will be returned.\n"
    "    The function expect only one positional argument.\n"
    "    For backwards-compatability, you may call this option `key` instead\n"
    "    of `on_fail`, but this is deprecated behavior.\n"
    "nan : optional\n"
    "    If the input value is NAN or can be parsed as NAN, return this\n"
    "    value instead of NAN.\n"
    "inf : optional\n"
    "    If the input value is INF or can be parsed as INF, return this\n"
    "    value instead of INF.\n"
    "allow_underscores : bool, optional\n"
    "    Starting with Python 3.6, underscores are allowed in numeric literals\n"
    "    and in strings passed to `int` or `float` (see PEP 515 for details on\n"
    "    what is and is not allowed). You can disable that behavior by setting\n"
    "    this option to *False* - the default is *True*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "out : {str, float}\n"
    "    If the input could be converted to a `float` the return type will\n"
    "    be `float`. Otherwise, the input `str` will be returned as-is\n"
    "    (if `raise_on_invalid` is *False*) or whatever value\n"
    "    is assigned to *default* if *default* is not *None*.\n"
    "\n"
    "Raises\n"
    "------\n"
    "TypeError\n"
    "    If the input is not one of `str`, `float`, or `int`.\n"
    "ValueError\n"
    "    If `raise_on_invalid` is *True*, this will be raised if the input\n"
    "    string cannot be converted to a `float`.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "check_float\n"
    "float\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import fast_float\n"
    "    >>> fast_float('56')\n"
    "    56.0\n"
    "    >>> fast_float('56.0')\n"
    "    56.0\n"
    "    >>> fast_float('56.07')\n"
    "    56.07\n"
    "    >>> fast_float('56.07 lb')\n"
    "    '56.07 lb'\n"
    "    >>> fast_float(56.07)\n"
    "    56.07\n"
    "    >>> fast_float(56)\n"
    "    56.0\n"
    "    >>> fast_float('invalid', default=50)\n"
    "    50\n"
    "    >>> fast_float('invalid', 50)  # 'default' is first optional positional arg\n"
    "    50\n"
    "    >>> fast_float('nan')\n"
    "    nan\n"
    "    >>> fast_float('nan', nan=0.0)\n"
    "    0.0\n"
    "    >>> fast_float('56.07', nan=0.0)\n"
    "    56.07\n"
    "    >>> fast_float('56.07 lb', raise_on_invalid=True) #doctest: "
    "+IGNORE_EXCEPTION_DETAIL\n"
    "    Traceback (most recent call last):\n"
    "      ...\n"
    "    ValueError: could not convert string to float: '56.07 lb'\n"
    "    >>> fast_float('invalid', on_fail=len)\n"
    "    7\n"
    "\n"
    "Notes\n"
    "-----\n"
    "It is roughly equivalent to (but much faster than)\n"
    "\n"
    "    >>> def py_fast_float(input, default=None, raise_on_invalid=False,\n"
    "    ...                   on_fail=None, nan=None, inf=None):\n"
    "    ...     try:\n"
    "    ...         x = float(input)\n"
    "    ...     except ValueError:\n"
    "    ...         if raise_on_invalid:\n"
    "    ...             raise\n"
    "    ...         elif on_fail is not None:\n"
    "    ...             return on_fail(input)\n"
    "    ...         elif default is not None:\n"
    "    ...             return default\n"
    "    ...         else:\n"
    "    ...             return input\n"
    "    ...     else:\n"
    "    ...         if nan is not None and math.isnan(x):\n"
    "    ...             return nan\n"
    "    ...         elif inf is not None and math.isinf(x):\n"
    "    ...             return inf\n"
    "    ...         else:\n"
    "    ...             return x\n"
    "    ... \n"
    "\n"
);

PyDoc_STRVAR(
    fast_int__doc__,
    "fast_int(x, default=None, raise_on_invalid=False, on_fail=None, base=10, "
    "allow_underscores=True)\n"
    "Quickly convert input to an `int`.\n"
    "\n"
    "Any input that is valid for the built-in `int`\n"
    "function will be converted to a `int`. An input\n"
    "of a single digit unicode character is also valid. The return value\n"
    "is guaranteed to be of type `str` or `int`.\n"
    "\n"
    "If the given input is a string and cannot be converted to an `int`\n"
    "it will be returned as-is unless `default` or `raise_on_invalid`\n"
    "is given.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input : {str, float, int, long}\n"
    "    The input you wish to convert to an `int`.\n"
    "default : optional\n"
    "    This value will be returned instead of the input\n"
    "    when the input cannot be converted. Has no effect if\n"
    "    *raise_on_invalid* is *True*.\n"
    "raise_on_invalid : bool, optional\n"
    "    If *True*, a `ValueError` will be raised if string input cannot be\n"
    "    converted to an `int`. If *False*, the string will be\n"
    "    returned as-is. The default is *False*.\n"
    "on_fail : callable, optional\n"
    "    If given and the *input* cannot be converted, the input will be\n"
    "    passed to the callable object and its return value will be returned.\n"
    "    The function expect only one positional argument.\n"
    "    For backwards-compatability, you may call this option `key` instead\n"
    "    of `on_fail`, but this is deprecated behavior.\n"
    "base : int, optional\n"
    "    Follows the rules of Python's built-in :func:`int`; see it's\n"
    "    documentation for your Python version. If given, the input\n"
    "    **must** be of type `str`.\n"
    "allow_underscores : bool, optional\n"
    "    Starting with Python 3.6, underscores are allowed in numeric literals\n"
    "    and in strings passed to `int` or `float` (see PEP 515 for details on\n"
    "    what is and is not allowed). You can disable that behavior by setting\n"
    "    this option to *False* - the default is *True*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "out : {str, int}\n"
    "    If the input could be converted to an `int`, the return type will be\n"
    "    `int`.\n"
    "    Otherwise, the input `str` will be returned as-is\n"
    "    (if `raise_on_invalid` is *False*) or whatever value\n"
    "    is assigned to *default* if *default* is not *None*.\n"
    "\n"
    "Raises\n"
    "------\n"
    "TypeError\n"
    "    If the input is not one of `str`, `float`, or `int`.\n"
    "ValueError\n"
    "    If `raise_on_invalid` is *True*, this will be raised if the input\n"
    "    string cannot be converted to an `int`.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "fast_forceint\n"
    "check_int\n"
    "int\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import fast_int\n"
    "    >>> fast_int('56')\n"
    "    56\n"
    "    >>> fast_int('56.0')\n"
    "    '56.0'\n"
    "    >>> fast_int('56.07 lb')\n"
    "    '56.07 lb'\n"
    "    >>> fast_int(56.07)\n"
    "    56\n"
    "    >>> fast_int(56)\n"
    "    56\n"
    "    >>> fast_int('invalid', default=50)\n"
    "    50\n"
    "    >>> fast_int('invalid', 50)  # 'default' is first optional positional arg\n"
    "    50\n"
    "    >>> fast_int('56.07 lb', raise_on_invalid=True) #doctest: "
    "+IGNORE_EXCEPTION_DETAIL\n"
    "    Traceback (most recent call last):\n"
    "      ...\n"
    "    ValueError: could not convert string to int: '56.07 lb'\n"
    "    >>> fast_int('invalid', on_fail=len)\n"
    "    7\n"
    "\n"
    "Notes\n"
    "-----\n"
    "It is roughly equivalent to (but much faster than)\n"
    "\n"
    "    >>> def py_fast_int(input, default=None, raise_on_invalid=False, "
    "on_fail=None):\n"
    "    ...     try:\n"
    "    ...         return int(input)\n"
    "    ...     except ValueError:\n"
    "    ...         if raise_on_invalid:\n"
    "    ...             raise\n"
    "    ...         elif on_fail is not None:\n"
    "    ...             return on_fail(input)\n"
    "    ...         elif default is not None:\n"
    "    ...             return default\n"
    "    ...         else:\n"
    "    ...             return input\n"
    "    ... \n"
    "\n"
);

PyDoc_STRVAR(
    fast_forceint__doc__,
    "fast_forceint(x, default=None, raise_on_invalid=False, on_fail=None, "
    "allow_underscores=True)\n"
    "Quickly convert input to an `int`, truncating if is a `float`.\n"
    "\n"
    "Any input that is valid for the built-in `int`\n"
    "function will be converted to a `int`. An input\n"
    "of a single numeric unicode character is also valid. The return value\n"
    "is guaranteed to be of type `str` or `int`.\n"
    "\n"
    "In addition to the above, any input valid for the built-in `float` will\n"
    "be parsed and the truncated to the nearest integer; for example, '56.07'\n"
    "will be converted to `56`.\n"
    "\n"
    "If the given input is a string and cannot be converted to an `int`\n"
    "it will be returned as-is unless `default` or `raise_on_invalid`\n"
    "is given.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input : {str, float, int, long}\n"
    "    The input you wish to convert to an `int`.\n"
    "default : optional\n"
    "    This value will be returned instead of the input\n"
    "    when the input cannot be converted. Has no effect if\n"
    "    *raise_on_invalid* is *True*\n"
    "raise_on_invalid : bool, optional\n"
    "    If *True*, a `ValueError` will be raised if string input cannot be\n"
    "    converted to an `int`.  If *False*, the string will be\n"
    "    returned as-is.  The default is *False*.\n"
    "on_fail : callable, optional\n"
    "    If given and the *input* cannot be converted, the input will be\n"
    "    passed to the callable object and its return value will be returned.\n"
    "    The function expect only one positional argument.\n"
    "    For backwards-compatability, you may call this option `key` instead\n"
    "    of `on_fail`, but this is deprecated behavior.\n"
    "allow_underscores : bool, optional\n"
    "    Starting with Python 3.6, underscores are allowed in numeric literals\n"
    "    and in strings passed to `int` or `float` (see PEP 515 for details on\n"
    "    what is and is not allowed). You can disable that behavior by setting\n"
    "    this option to *False* - the default is *True*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "out : {str, int}\n"
    "    If the input could be converted to an `int`, the return type will be\n"
    "    `int`.\n"
    "    Otherwise, the input `str` will be returned as-is\n"
    "    (if `raise_on_invalid` is *False*) or whatever value\n"
    "    is assigned to *default* if *default* is not *None*.\n"
    "\n"
    "Raises\n"
    "------\n"
    "TypeError\n"
    "    If the input is not one of `str`, `float`, or `int`.\n"
    "ValueError\n"
    "    If `raise_on_invalid` is *True*, this will be raised if the input\n"
    "    string cannot be converted to an `int`.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "fast_int\n"
    "check_intlike\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import fast_forceint\n"
    "    >>> fast_forceint('56')\n"
    "    56\n"
    "    >>> fast_forceint('56.0')\n"
    "    56\n"
    "    >>> fast_forceint('56.07')\n"
    "    56\n"
    "    >>> fast_forceint('56.07 lb')\n"
    "    '56.07 lb'\n"
    "    >>> fast_forceint(56.07)\n"
    "    56\n"
    "    >>> fast_forceint(56)\n"
    "    56\n"
    "    >>> fast_forceint('invalid', default=50)\n"
    "    50\n"
    "    >>> fast_forceint('invalid', 50)  # 'default' is first optional positional "
    "arg\n"
    "    50\n"
    "    >>> fast_forceint('56.07 lb', raise_on_invalid=True) #doctest: "
    "+IGNORE_EXCEPTION_DETAIL\n"
    "    Traceback (most recent call last):\n"
    "      ...\n"
    "    ValueError: could not convert string to float: '56.07 lb'\n"
    "    >>> fast_forceint('invalid', on_fail=len)\n"
    "    7\n"
    "\n"
    "Notes\n"
    "-----\n"
    "It is roughly equivalent to (but much faster than)\n"
    "\n"
    "    >>> def py_fast_forceint(input, default=None, raise_on_invalid=False, "
    "on_fail=None):\n"
    "    ...     try:\n"
    "    ...         return int(input)\n"
    "    ...     except ValueError:\n"
    "    ...         try:\n"
    "    ...             return int(float(input))\n"
    "    ...         except ValueError:\n"
    "    ...             if raise_on_invalid:\n"
    "    ...                 raise\n"
    "    ...             elif on_fail is not None:\n"
    "    ...                 return on_fail(input)\n"
    "    ...             elif default is not None:\n"
    "    ...                 return default\n"
    "    ...             else:\n"
    "    ...                 return input\n"
    "    ... \n"
    "\n"
);

PyDoc_STRVAR(
    check_real__doc__,
    "check_real(x, *, consider=None, inf=fastnumbers.NUMBER_ONLY, "
    "nan=fastnumbers.NUMBER_ONLY, "
    "allow_underscores=False)\n"
    "Quickly determine if a string is a real number.\n"
    "\n"
    "Returns *True* if the input is valid input for the built-in `float` or\n"
    "`int` functions, or is a single valid numeric unicode character.\n"
    "\n"
    "The input may be whitespace-padded.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input :\n"
    "    The input you wish to test if it is a real number.\n"
    "consider : optional\n"
    "    Control the data types that may be interpreted. By default both string and\n"
    "    numeric input may be considered. If given *STRING_ONLY*, then only string\n"
    "    input may return *True*. if given *NUMBER_ONLY*, then only numeric input\n"
    "    may return *True*. Giving *None* is equivalent to omitting this argument.\n"
    "inf : optional\n"
    "    Control if and in what form INF is interpreted. The default is *NUMBER_ONLY*,\n"
    "    which indicates that only INF will return *True*. Other allowed values are\n"
    "    *STRING_ONLY*, which indicates that only \"inf\" will return *True*,\n"
    "    *ALLOWED*, which indicates that both \"inf\" and INF will return *True*,\n"
    "    or *DISALLOWED*, which means neither will return *True*.\n"
    "nan : optional\n"
    "    Control if and in what form NaN is interpreted. Behavior matches that of\n"
    "    `inf` except it is for the string \"nan\" and the value NaN.\n"
    "allow_underscores : bool, optional\n"
    "    Underscores are allowed in numeric literals and in strings passed to `int`\n"
    "    or `float` (see PEP 515 for details on what is and is not allowed). You can\n"
    "    enable that behavior by setting this option to *True* - the default is "
    "*False*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "result : bool\n"
    "    Whether or not the input is a real number.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "fast_real\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import ALLOWED, DISALLOWED, NUMBER_ONLY, STRING_ONLY, "
    "check_real\n"
    "    >>> check_real('56')\n"
    "    True\n"
    "    >>> check_real('56.07')\n"
    "    True\n"
    "    >>> check_real('56.07', consider=NUMBER_ONLY)\n"
    "    False\n"
    "    >>> check_real('56.07 lb')\n"
    "    False\n"
    "    >>> check_real(56.07)\n"
    "    True\n"
    "    >>> check_real(56.07, consider=STRING_ONLY)\n"
    "    False\n"
    "    >>> check_real(56)\n"
    "    True\n"
    "    >>> check_real('nan')\n"
    "    False\n"
    "    >>> check_real('nan', nan=ALLOWED)\n"
    "    True\n"
    "    >>> check_real(float('nan'))\n"
    "    True\n"
    "    >>> check_real(float('nan'), nan=DISALLOWED)\n"
    "    False\n"
    "\n"
);

PyDoc_STRVAR(
    check_float__doc__,
    "check_float(x, *, consider=None, inf=fastnumbers.NUMBER_ONLY, "
    "nan=fastnumbers.NUMBER_ONLY, "
    "strict=False, allow_underscores=False)\n"
    "Quickly determine if a string is a `float`.\n"
    "\n"
    "Returns *True* if the input is valid input for the built-in `float`\n"
    "function, is already a valid `float`, or is a single valid numeric unicode\n"
    "character. It differs from `check_real` in that an `int` input will return\n"
    "*False*.\n"
    "\n"
    "The input may be whitespace-padded.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input :\n"
    "    The input you wish to test if it is a `float`.\n"
    "consider : optional\n"
    "    Control the data types that may be interpreted. By default both string and\n"
    "    numeric input may be considered. If given *STRING_ONLY*, then only string\n"
    "    input may return *True*. if given *NUMBER_ONLY*, then only numeric input\n"
    "    may return *True*. Giving *None* is equivalent to omitting this argument.\n"
    "inf : optional\n"
    "    Control if and in what form INF is interpreted. The default is *NUMBER_ONLY*,\n"
    "    which indicates that only INF will return *True*. Other allowed values are\n"
    "    *STRING_ONLY*, which indicates that only \"inf\" will return *True*,\n"
    "    *ALLOWED*, which indicates that both \"inf\" and INF will return *True*,\n"
    "    or *DISALLOWED*, which means neither will return *True*.\n"
    "nan : optional\n"
    "    Control if and in what form NaN is interpreted. Behavior matches that of\n"
    "    `inf` except it is for the string \"nan\" and the value NaN.\n"
    "strict : bool, optional\n"
    "    Control whether a string must be strictly represented as a float. If *True*,\n"
    "    then the string \"56.0\" would return *True* but \"56\" would return *False*.\n"
    "    If *False* (the default), then both of the strings \"56.0\" and \"56\" would\n"
    "    return *True*.\n"
    "allow_underscores : bool, optional\n"
    "    Underscores are allowed in numeric literals and in strings passed to `int`\n"
    "    or `float` (see PEP 515 for details on what is and is not allowed). You can\n"
    "    enable that behavior by setting this option to *True* - the default is "
    "*False*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "result : bool\n"
    "    Whether or not the input is a `float`.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "fast_float\n"
    "check_real\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import ALLOWED, DISALLOWED, NUMBER_ONLY, STRING_ONLY, "
    "check_float\n"
    "    >>> check_float('56')\n"
    "    True\n"
    "    >>> check_float('56', strict=True)\n"
    "    False\n"
    "    >>> check_float('56.07')\n"
    "    True\n"
    "    >>> check_float('56.07', consider=NUMBER_ONLY)\n"
    "    False\n"
    "    >>> check_float('56.07 lb')\n"
    "    False\n"
    "    >>> check_float(56.07)\n"
    "    True\n"
    "    >>> check_float(56.07, consider=STRING_ONLY)\n"
    "    False\n"
    "    >>> check_float(56)\n"
    "    False\n"
    "    >>> check_float('nan')\n"
    "    False\n"
    "    >>> check_float('nan', nan=ALLOWED)\n"
    "    True\n"
    "    >>> check_float(float('nan'))\n"
    "    True\n"
    "    >>> check_float(float('nan'), nan=DISALLOWED)\n"
    "    False\n"
    "\n"
);

PyDoc_STRVAR(
    check_int__doc__,
    "check_int(x, *, consider=None, base=10, allow_underscores=False)\n"
    "Quickly determine if a string is an `int`.\n"
    "\n"
    "Returns *True* if the input is valid input for the built-in `int`\n"
    "function, is already a valid `int`, or is a single valid digit unicode\n"
    "character. It differs from `check_intlike` in that a `float` input will\n"
    "return *False* and that `int`-like strings (i.e. '45.0') will return\n"
    "*False*.\n"
    "\n"
    "The input may be whitespace-padded.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input :\n"
    "    The input you wish to test if it is an `int`.\n"
    "consider : optional\n"
    "    Control the data types that may be interpreted. By default both string and\n"
    "    numeric input may be considered. If given *STRING_ONLY*, then only string\n"
    "    input may return *True*. if given *NUMBER_ONLY*, then only numeric input\n"
    "    may return *True*. Giving *None* is equivalent to omitting this argument.\n"
    "base : int, optional\n"
    "    Follows the rules of Python's built-in :func:`int`; see it's\n"
    "    documentation for your Python version. Ignored unless the input is\n"
    "    of type `str`.\n"
    "allow_underscores : bool, optional\n"
    "    Underscores are allowed in numeric literals and in strings passed to `int`\n"
    "    or `float` (see PEP 515 for details on what is and is not allowed). You can\n"
    "    enable that behavior by setting this option to *True* - the default is "
    "*False*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "result : bool\n"
    "    Whether or not the input is an `int`.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "fast_int\n"
    "check_intlike\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import NUMBER_ONLY, STRING_ONLY, check_int\n"
    "    >>> check_int('56')\n"
    "    True\n"
    "    >>> check_int('56', consider=NUMBER_ONLY)\n"
    "    False\n"
    "    >>> check_int('56.07')\n"
    "    False\n"
    "    >>> check_int('56.07 lb')\n"
    "    False\n"
    "    >>> check_int('13af')\n"
    "    False\n"
    "    >>> check_int('13af', base=16)\n"
    "    True\n"
    "    >>> check_int('0x13af')\n"
    "    False\n"
    "    >>> check_int('0x13af', base=0)  # detect base from prefix\n"
    "    True\n"
    "    >>> check_int(56.07)\n"
    "    False\n"
    "    >>> check_int(56)\n"
    "    True\n"
    "    >>> check_int(56, consider=STRING_ONLY)\n"
    "    False\n"
    "\n"
);

PyDoc_STRVAR(
    check_intlike__doc__,
    "check_intlike(x, *, consider=None, allow_underscores=False)\n"
    "Quickly determine if a string (or object) is an `int` or `int`-like.\n"
    "\n"
    "Returns *True* if the input is valid input for the built-in `int`\n"
    "function, is already a valid `int` or `float`, or is a single valid\n"
    "numeric unicode character. It differs from `int` in that `int`-like\n"
    "floats or strings (i.e. '45.0') will return *True*.\n"
    "\n"
    "The input may be whitespace-padded.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input :\n"
    "    The input you wish to test if it is a `int`-like.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "result : bool\n"
    "    Whether or not the input is an `int` or int-like.\n"
    "consider : optional\n"
    "    Control the data types that may be interpreted. By default both string and\n"
    "    numeric input may be considered. If given *STRING_ONLY*, then only string\n"
    "    input may return *True*. if given *NUMBER_ONLY*, then only numeric input\n"
    "    may return *True*. Giving *None* is equivalent to omitting this argument.\n"
    "allow_underscores : bool, optional\n"
    "    Underscores are allowed in numeric literals and in strings passed to `int`\n"
    "    or `float` (see PEP 515 for details on what is and is not allowed). You can\n"
    "    enable that behavior by setting this option to *True* - the default is "
    "*False*.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "fast_forceint\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import NUMBER_ONLY, STRING_ONLY, check_intlike\n"
    "    >>> check_intlike('56')\n"
    "    True\n"
    "    >>> check_intlike('56', consider=NUMBER_ONLY)\n"
    "    False\n"
    "    >>> check_intlike('56.07')\n"
    "    False\n"
    "    >>> check_intlike('56.0')\n"
    "    True\n"
    "    >>> check_intlike('56.07 lb')\n"
    "    False\n"
    "    >>> check_intlike(56.07)\n"
    "    False\n"
    "    >>> check_intlike(56.0)\n"
    "    True\n"
    "    >>> check_intlike(56.0, consider=STRING_ONLY)\n"
    "    False\n"
    "    >>> check_intlike(56)\n"
    "    True\n"
    "\n"
);

PyDoc_STRVAR(
    isreal__doc__,
    "isreal(x, *, str_only=False, num_only=False, allow_inf=False, allow_nan=False, "
    "allow_underscores=True)\n"
    "Quickly determine if a string is a real number.\n"
    "\n"
    "Identical in functionality to :func:`check_real` but with a different API\n"
    "that has the following differences:\n"
    "\n"
    "  * `allow_underscores` is *True* by default, not *False*.\n"
    "  * instead of `consider`, there are two separate `bool` options `str_only`\n"
    "    and `num_only`.\n"
    "  * `allow_nan` is a `bool` that can only only tolggle behavior of\n"
    "    \"nan\"; NaN will always return *True*.\n"
    "  * `allow_inf` is a `bool` that can only only tolggle behavior of\n"
    "    \"inf\"; INF will always return *True*.\n"
    "\n"
);

PyDoc_STRVAR(
    isfloat__doc__,
    "isfloat(x, *, str_only=False, num_only=False, allow_inf=False, allow_nan=False, "
    "allow_underscores=True)\n"
    "Quickly determine if a string is a `float`.\n"
    "\n"
    "Identical in functionality to :func:`check_float` but with a different API\n"
    "that has the following differences:\n"
    "\n"
    "  * `allow_underscores` is *True* by default, not *False*.\n"
    "  * instead of `consider`, there are two separate `bool` options `str_only`\n"
    "    and `num_only`.\n"
    "  * `allow_nan` is a `bool` that can only only tolggle behavior of\n"
    "    \"nan\"; NaN will always return *True*.\n"
    "  * `allow_inf` is a `bool` that can only only tolggle behavior of\n"
    "    \"inf\"; INF will always return *True*.\n"
    "  * there is no `strict` option to toggle how strings containing integers\n"
    "    are evaluated."
    "\n"
);

PyDoc_STRVAR(
    isint__doc__,
    "isint(x, *, str_only=False, num_only=False, base=10, allow_underscores=True)\n"
    "Quickly determine if a string is an `int`.\n"
    "\n"
    "Identical in functionality to :func:`check_int` but with a different API\n"
    "that has the following differences:\n"
    "\n"
    "  * `allow_underscores` is *True* by default, not *False*.\n"
    "  * instead of `consider`, there are two separate `bool` options `str_only`\n"
    "    and `num_only`.\n"
    "\n"
);

PyDoc_STRVAR(
    isintlike__doc__,
    "isintlike(x, *, str_only=False, num_only=False, allow_underscores=True)\n"
    "Quickly determine if a string (or object) is an `int` or `int`-like.\n"
    "\n"
    "Identical in functionality to :func:`check_intlike` but with a different API\n"
    "that has the following differences:\n"
    "\n"
    "  * `allow_underscores` is *True* by default, not *False*.\n"
    "  * instead of `consider`, there are two separate `bool` options `str_only`\n"
    "    and `num_only`.\n"
    "\n"
);

PyDoc_STRVAR(
    query_type__doc__,
    "query_type(x, *, allow_inf=False, allow_nan=False, coerce=False, allowed_types=*, "
    "allow_underscores=True)\n"
    "Quickly determine the type that fastnumbers would return for a given input.\n"
    "\n"
    "For string or bytes-like input, the contents of the string will be examined and\n"
    "the type *int* or *float* will be returned if the object contains a "
    "representation\n"
    "of an *int* or *float*, respectively. For all other cases, the type of the input\n"
    "object is returned, just like the built-in function *type*.\n"
    "\n"
    "The input may be whitespace-padded.\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "input :\n"
    "    The input of which you wish to query the type fastnumbers might return.\n"
    "allow_inf : bool, optional\n"
    "    If *True*, then the strings 'inf' and 'infinity' will also return *float*.\n"
    "    This check is case-insensitive, and the string may be signed (i.e. '+/-').\n"
    "    The default is *False*.\n"
    "allow_nan : bool, optional\n"
    "    If *True*, then the string 'nan' will also return *float*.\n"
    "    This check is case-insensitive, and the string may be signed (i.e. '+/-').\n"
    "    The default is *False*.\n"
    "coerce : bool, optional\n"
    "    If *True*, then numbers that are given as *float* but could be converted to\n"
    "    an *int* without loss of precision will return type *int* instead of *float*.\n"
    "allowed_types : sequence of types, optional\n"
    "    If given, then only the given types may be returned, and anything else will\n"
    "    return *None*.\n"
    "allow_underscores : bool, optional\n"
    "    Starting with Python 3.6, underscores are allowed in numeric literals\n"
    "    and in strings passed to `int` or `float` (see PEP 515 for details on\n"
    "    what is and is not allowed). You can disable that behavior by setting\n"
    "    this option to *False* - the default is *True*.\n"
    "\n"
    "Returns\n"
    "-------\n"
    "result : type\n"
    "    The type that fastnumbers might return for the given input.\n"
    "\n"
    "See Also\n"
    "--------\n"
    "check_real\n"
    "check_float\n"
    "check_int\n"
    "check_intlike\n"
    "\n"
    "Examples\n"
    "--------\n"
    "\n"
    "    >>> from fastnumbers import query_type\n"
    "    >>> query_type('56')\n"
    "    <class 'int'>\n"
    "    >>> query_type('56.07')\n"
    "    <class 'float'>\n"
    "    >>> query_type('56.07 lb')\n"
    "    <class 'str'>\n"
    "    >>> query_type('56.07 lb', allowed_types=(float, int))  # returns None\n"
    "    >>> query_type('56.0')\n"
    "    <class 'float'>\n"
    "    >>> query_type('56.0', coerce=True)\n"
    "    <class 'int'>\n"
    "    >>> query_type(56.07)\n"
    "    <class 'float'>\n"
    "    >>> query_type(56)\n"
    "    <class 'int'>\n"
    "    >>> query_type('nan')\n"
    "    <class 'str'>\n"
    "    >>> query_type('nan', allow_nan=True)\n"
    "    <class 'float'>\n"
    "\n"
);

PyDoc_STRVAR(
    fastnumbers_int__doc__,
    "int(x=0, base=10)\n"
    "Drop-in but faster replacement for the built-in *int*.\n"
    "\n"
    "Behaves identically to the built-in *int* except for the following:\n"
    "\n"
    "    - Cannot convert from the ``__trunc__`` special method of an object.\n"
    "    - Is implemented as a function, not a class, which means it cannot be\n"
    "      sub-classed, and has no *from_bytes* classmethod.\n"
    "    - You cannot use this function in ``isinstance``.\n"
    "\n"
    "If you need any of the above functionality you can still access the original\n"
    "*int* class through ``builtins``.\n"
    "\n"
    "    >>> from fastnumbers import int\n"
    "    >>> isinstance(9, int) # doctest: +ELLIPSIS\n"
    "    Traceback (most recent call last):\n"
    "        ...\n"
    "    TypeError: ...\n"
    "    >>> import builtins\n"
    "    >>> isinstance(9, builtins.int)\n"
    "    True\n"
    "\n"
    "\n"
);

PyDoc_STRVAR(
    fastnumbers_float__doc__,
    "float(x=0)\n"
    "Drop-in but faster replacement for the built-in *float*.\n"
    "\n"
    "Behaves identically to the built-in *float* except for the following:\n"
    "\n"
    "    - Is implemented as a function, not a class, which means it cannot be\n"
    "      sub-classed, and has no *fromhex* classmethod.\n"
    "    - A *ValueError* will be raised instead of a *UnicodeEncodeError*\n"
    "      if a partial surrogate is given as input.\n"
    "    - You cannot use this function in ``isinstance``.\n"
    "\n"
    "If you need any of the above functionality you can still access the original\n"
    "*float* class through ``builtins``.\n"
    "\n"
    "    >>> from fastnumbers import float\n"
    "    >>> isinstance(9.4, float)  # doctest: +ELLIPSIS\n"
    "    Traceback (most recent call last):\n"
    "        ...\n"
    "    TypeError: ...\n"
    "    >>> import builtins\n"
    "    >>> isinstance(9.4, builtins.float)\n"
    "    True\n"
    "\n"
    "\n"
);

PyDoc_STRVAR(
    fastnumbers_real__doc__,
    "real(x=0.0, coerce=True)\n"
    "Convert to *float* or *int*, whichever is most appropriate.\n"
    "\n"
    "If an *int* literal or string containing an *int* is provided,\n"
    "then an *int* will be returned. If a *float* literal or a string\n"
    "containing a non-*int* and non-*complex* number is provided,\n"
    "a *float* will be returned.\n"
    "\n"
    "If *coerce* is *True* (the default), then if a *float* is given\n"
    "that has no decimal places after conversion or only zeros after\n"
    "the decimal point, it will be returned as an *int* instead of a\n"
    "*float*.\n"
    "\n"
);

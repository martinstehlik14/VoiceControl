#ifdef DEBUG_MODE
  #define DBG(...)         Serial.printf(__VA_ARGS__)
  #define DBG_CODE(...)  __VA_ARGS__
  #define DBG_VAR(...)   __VA_ARGS__
#else
  #define DBG(...)         ((void)0)
  #define DBG_CODE(...)  
  #define DBG_VAR(...)   
#endif
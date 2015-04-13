\#if defined(MOZJS_MAJOR_VERSION)
bool js_${generator.prefix}_${class_name}_${func_name}(JSContext *cx, uint32_t argc, jsval *vp);
\#elif defined(JS_VERSION)
JSBool js_${generator.prefix}_${class_name}_${func_name}(JSContext *cx, uint32_t argc, jsval *vp);
\#endif

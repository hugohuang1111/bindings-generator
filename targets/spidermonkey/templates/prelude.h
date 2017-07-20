#set generator = $current_class.generator

\#if MOZJS_MAJOR_VERSION >= 33
void js_register_${generator.prefix}_${current_class.class_name}(JSContext *cx, JS::HandleObject global);
void register_all_${generator.prefix}(JSContext* cx, JS::HandleObject obj);
\#else
void js_register_${generator.prefix}_${current_class.class_name}(JSContext *cx, JSObject* global);
void register_all_${generator.prefix}(JSContext* cx, JSObject* obj);
\#endif

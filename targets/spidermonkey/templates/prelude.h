#set generator = $current_class.generator

extern JSClass  *jsb_${current_class.underlined_class_name}_class;
extern JSObject *jsb_${current_class.underlined_class_name}_prototype;

\#if MOZJS_MAJOR_VERSION >= 33
void js_register_${generator.prefix}_${current_class.class_name}(JSContext *cx, JS::HandleObject global);
void register_all_${generator.prefix}(JSContext* cx, JS::HandleObject obj);
\#else
void js_register_${generator.prefix}_${current_class.class_name}(JSContext *cx, JSObject* global);
void register_all_${generator.prefix}(JSContext* cx, JSObject* obj);
\#endif

bool js_${generator.prefix}_${current_class.class_name}_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_${generator.prefix}_${current_class.class_name}_finalize(JSContext *cx, JSObject *obj);

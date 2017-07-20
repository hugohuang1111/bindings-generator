#set generator = $current_class.generator
JSClass  *jsb_${current_class.underlined_class_name}_class;
\#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_${current_class.underlined_class_name}_prototype;
\#endif

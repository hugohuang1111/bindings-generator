\#if defined(MOZJS_MAJOR_VERSION)
\#if MOZJS_MAJOR_VERSION >= 33
void register_all_${prefix}(JSContext* cx, JS::HandleObject obj) {
    #if $target_ns
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "${target_ns}", &ns);
    #end if

    #for jsclass in $sorted_classes
    #if $in_listed_classes(jsclass)
    js_register_${prefix}_${jsclass}(cx, ns);
    #end if
    #end for

    sdkbox::Sdkbox::setProjectType("js");
}
\#else
void register_all_${prefix}(JSContext* cx, JSObject* obj) {
    #if $target_ns
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "${target_ns}", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "${target_ns}", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;
    #end if

    #for jsclass in $sorted_classes
    #if $in_listed_classes(jsclass)
    js_register_${prefix}_${jsclass}(cx, obj);
    #end if
    #end for

    sdkbox::Sdkbox::setProjectType("js");
}
\#endif
\#elif defined(JS_VERSION)
void register_all_${prefix}(JSContext* cx, JSObject* obj) {
    #if $target_ns
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, obj, "${target_ns}", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "${target_ns}", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;
    #end if

    #for jsclass in $sorted_classes
    #if $in_listed_classes(jsclass)
    js_register_${prefix}_${jsclass}(cx, obj);
    #end if
    #end for

    sdkbox::Sdkbox::setProjectType("js");
}
\#endif
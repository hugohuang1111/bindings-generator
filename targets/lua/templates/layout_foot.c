TOLUA_API int register_all_${prefix}(lua_State* tolua_S)
{
	tolua_open(tolua_S);

	#if $target_ns
	std::stringstream ss("${target_ns}");
    std::vector<std::string> nsvec;
    std::string item;
    while (std::getline(ss, item, '.')) {
        nsvec.push_back(item);
    }
    int nsLen = nsvec.size();
    item = nsvec.front();
    nsvec.erase(nsvec.begin());

    tolua_module(tolua_S, item.c_str(), 0);
    tolua_beginmodule(tolua_S, item.c_str());

    while (nsvec.size() > 0) {
        item = nsvec.front();
        nsvec.erase(nsvec.begin());
        lua_pushstring(tolua_S, item.c_str()); // m name
        lua_rawget(tolua_S, -2);             // m value
        if (!lua_istable(tolua_S, -1)) {
            lua_pop(tolua_S, 1);             // m
            lua_newtable(tolua_S);           // m t
            lua_pushstring(tolua_S, item.c_str()); // m t name
            lua_pushvalue(tolua_S, -2);      // m t name t
            lua_rawset(tolua_S, -4);         // m t
        }
    }
	#else
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);
	#end if

	#for jsclass in $sorted_classes
	#if $in_listed_classes(jsclass)
	lua_register_${prefix}_${jsclass}(tolua_S);
	#end if
	#end for

	#if $target_ns
	if (nsLen > 1) {
        lua_pop(tolua_S, nsLen - 1); // m
    }
    #end if
	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

#if $macro_judgement
\#endif
#end if

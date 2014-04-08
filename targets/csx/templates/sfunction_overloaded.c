
## ===== static overloaded function implementation template
void ${signature_name}(ObjectInterface::tHandle object, QVariant& retVar, int argc, va_list args)
{
## ====== Generate function calls
#for func in $implementations
#if len($func.arguments) >= $func.min_args
	#set arg_count = len($func.arguments)
	#set arg_idx = $func.min_args
	#while $arg_idx <= $arg_count
	if(argc == ${arg_idx})
	{
		## ====== Populate parameters
		#set $count = 0;
		#while $count < $arg_idx
			#set $arg = $func.arguments[$count]
		#if $arg.has_to_native($generator)
		${arg.to_native({"generator": $generator,
								"in_value": "arg" + str(count),
								"out_value": "arg",
								"class_name": $class_name,
								"ntype": str($arg),
								"level": 2})};
		#else if $arg.is_reference
		${arg} arg${count} = *va_arg(args, $arg.to_string($generator)*);
		#else if $arg.is_pointer
		${arg} arg${count} = va_arg(args, $arg);
		#else if $arg.isPOD($generator)
		${arg} arg${count} = va_arg(args, $arg.to_string($generator));
		#else
		${arg} arg${count} = *va_arg(args, $arg*);
		#end if
			#set $count = $count + 1
		#end while
		## ===== generation agument list
		#set $count = 0
		#set arg_list = ""
		#set arg_array = []
		#while $count < $arg_idx
			#set $arg = $func.arguments[$count]
			#set $arg_array += ["arg"+str(count)]
			#set $count = $count + 1
		#end while
		#set $arg_list = ", ".join($arg_array)

		## ===== Call function
		#if $func.ret_type.name != "void"
			#if $func.ret_type.is_enum
		int ret = (int)$namespaced_class_name::${func.func_name}($arg_list);
			#else
		${func.ret_type.get_whole_name($generator)} ret = $namespaced_class_name::${func.func_name}($arg_list);
			#end if
			#if $func.ret_type.is_object and $func.ret_type.is_pointer
		auto service = CSX()->getService<ClassFactoryServiceInterface>();
		auto retObjVal = service->createObject(kcc$func.ret_type.base_name, (void*)ret);
		retVar.setValue(retObjVal);
			#else if $func.ret_type.has_from_native($generator)
		${func.ret_type.from_native({"generator": $generator,
								"in_value": "ret",
								"out_value": "qtret",
								"ntype": str($func.ret_type),
								"level": 3})};
		retVar.setValue(qtret);
			#else
		retVar.setValue(ret);
			#end if
		#else
		$namespaced_class_name::${func.func_name}($arg_list);
		#end if
	}
		#set $arg_idx = $arg_idx + 1
	#end while

#end if
#end for
}

## ===== static function implementation template
void ${signature_name}(ObjectInterface::tHandle object, QVariant& retVar, int argc, va_list args)
{
## ====== Generate function calls
#if len($arguments) >= $min_args
	#set arg_count = len($arguments)
	#set arg_idx = $min_args
	#while $arg_idx <= $arg_count
	if(argc == ${arg_idx})
	{
		## ====== Populate parameters
		#set $count = 0;
		#while $count < $arg_idx
			#set $arg = $arguments[$count]
		#if $arg.is_reference
		${arg} arg${count} = *va_arg(args, $arg.to_string($generator)*);
		#else if $arg.isPOD()
		${arg} arg${count} = *va_arg(args, $arg.to_string($generator)*);
		#else
		${arg} arg${count} = va_arg(args, $arg);
		#end if
			#set $count = $count + 1
		#end while
		## ===== generation agument list
		#set $count = 0
		#set arg_list = ""
		#set arg_array = []
		#while $count < $arg_idx
			#set $arg = $arguments[$count]
			#set $arg_array += ["arg"+str(count)]
			#set $count = $count + 1
		#end while
		#set $arg_list = ", ".join($arg_array)

		## ===== Call function
		#if $ret_type.name != "void"
			#if $ret_type.is_enum
		int ret = (int)$namespaced_class_name::${func_name}($arg_list);
			#else
		${ret_type.get_whole_name($generator)} ret = $namespaced_class_name::${func_name}($arg_list);
			#end if
			#if $ret_type.is_object and $ret_type.is_pointer
		auto service = CSX()->getService<ClassFactoryServiceInterface>();
		auto retObjVal = service->createObject(kcc$ret_type.base_name, (void*)ret);
		retVar.setValue(retObjVal);
			#else  if $ret_type.has_from_native($generator)
		${ret_type.from_native({"generator": $generator,
								"in_value": "ret",
								"out_value": "qtret",
								"ntype": str($ret_type),
								"level": 3})};
		retVar.setValue(qtret);
			#else
		retVar.setValue(ret);
			#end if
		#else
		$namespaced_class_name::${func_name}($arg_list);
		#end if
	}
		#set $arg_idx = $arg_idx + 1
	#end while

#end if
}
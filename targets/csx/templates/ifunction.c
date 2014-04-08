
## ===== instance function implementation template
void ${signature_name}(ObjectInterface::tHandle object, QVariant& retVar, int argc, va_list args)
{
#if not $is_constructor
	## ===== get the object from top of the stack
	$namespaced_class_name* obj = ($namespaced_class_name*)object;
#end if

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
			#set $arg = $arguments[$count]
			#set $arg_array += ["arg"+str(count)]
			#set $count = $count + 1
		#end while
		#set $arg_list = ", ".join($arg_array)

		## ===== Call function
		#if $ret_type.name != "void"
			#if $ret_type.is_enum
		int ret = (int)obj->${func_name}($arg_list);
			#else
		${ret_type.get_whole_name($generator)} ret = obj->${func_name}($arg_list);
			#end if
			## ----- Wrap object with csx Object if return value is a pointer to cc object
			#if $ret_type.is_object and $ret_type.is_pointer
		auto service = CSX()->getService<ClassFactoryServiceInterface>();
		auto retObjVal = service->createObject(kcc$ret_type.base_name, (void*)ret);
		retVar.setValue(retObjVal);
			## ===== Perform specialized type convertions here
			#else if $ret_type.has_from_native($generator)
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
		obj->${func_name}($arg_list);
		#end if
	}
		#set $arg_idx = $arg_idx + 1
	#end while

#end if
}

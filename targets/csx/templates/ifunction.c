
## ===== instance function implementation template
void ${signature_name}(CSXContext *cx, uint32_t argc)
{
#if not $is_constructor
	## ===== get the object from top of the stack
	$namespaced_class_name* obj = cx->top()->getValue<$namespaced_class_name*>();
	cx->pop();
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
		${arg} arg${count} = cx->top()->getValue<$arg>();
		cx->pop();
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
		Variant* retVar = new Variant();
		#if $ret_type.is_enum
		retVar->setValue<int>(ret);
		#else
		retVar->setValue<${ret_type.get_whole_name($generator)}>(ret);
		#end if
		cx->push(retVar);
		#else
		obj->${func_name}($arg_list);
		#end if
	}
		#set $arg_idx = $arg_idx + 1
	#end while

#end if
}

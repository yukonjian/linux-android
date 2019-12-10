Returns number of elements on sucess, -EINVAL if the property does
not exist or its length does not match a multiple of u32 and -ENODATA if the
property does not have a value.
  ret = of_property_count_u32_elems(np, propname);
	if (ret < 0) {
    /* 对于可有可无的属性可以使用该判据 */
		if (ret == -EINVAL) {
			/*
			 * -EINVAL means the property does not exist, this is
			 * fine.
			 */
			return 0;
		}

		dev_err(dev, "Property '%s' elems could not be read: %d\n",
			propname, ret);
		return ret;
	}

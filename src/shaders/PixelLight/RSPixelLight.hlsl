#define main "RootFlags (ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | " \
								"DENY_DOMAIN_SHADER_ROOT_ACCESS | " \
								"DENY_HULL_SHADER_ROOT_ACCESS | " \
								"DENY_GEOMETRY_SHADER_ROOT_ACCESS ), " \
			 "RootConstants(num32BitConstants = 16, b0, space=0, "\
									"visibility=SHADER_VISIBILITY_VERTEX),"\
			 "CBV(b1, space=0, visibility=SHADER_VISIBILITY_VERTEX,"\
									"flags = DATA_VOLATILE ),"\
			 "CBV(b0, space=1, visibility=SHADER_VISIBILITY_PIXEL,"\
									"flags = DATA_VOLATILE ),"\
			 "RootConstants(num32BitConstants = 15, b1, space=1, "\
									"visibility=SHADER_VISIBILITY_PIXEL),"
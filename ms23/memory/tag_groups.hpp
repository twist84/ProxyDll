#pragma once
#include <vector>

// this entire file could be a lot better

struct tag_block
{
	unsigned __int32 count;
	char *address;
	__int32 _bf8;
};

struct tag_reference
{
	unsigned __int32 group_tag;
	__int32 : 32;
	__int32 : 32;
	__int32 tag_index;
};


struct group_tag
{
	uint32_t group;
	const char *name;
	uint32_t size;

	void print_standard_enum_string()
	{
		printf_s("%s = 0x%X", name, group);
	}
};

struct tag
{
	group_tag tag_group;
	const char *name;
	uint16_t index;

	uint8_t *GetDefinition()
	{
		return ((uint8_t *(__cdecl *)(uint32_t, uint16_t))0x503370)(tag_group.group, index);
	}

	bool IsLoaded()
	{
		return ((int(__cdecl *)(uint32_t, uint16_t))0x503510)(tag_group.group, index);
	}
};

struct
{
	group_tag sound_effect_template = { '<fx>', "sound_effect_template", 0x20 };
	group_tag achievements = { 'achi', "achievements", 0x18 };
	group_tag ai_dialogue_globals = { 'adlg', "ai_dialogue_globals", 0x5C };
	group_tag ai_globals = { 'aigl', "ai_globals", 0x10 };
	group_tag antenna = { 'ant!', "antenna", 0x50 };
	group_tag device_arg_device = { 'argd', "device_arg_device", 0x4 };
	group_tag armor = { 'armr', "armor", 0x28 };
	group_tag armor_sounds = { 'arms', "armor_sounds", 0x10 };
	group_tag beam_system = { 'beam', "beam_system", 0x18 };
	group_tag bink = { 'bink', "bink", 0x18 };
	group_tag biped = { 'bipd', "biped", 0x240 };
	group_tag bitmap = { 'bitm', "bitmap", 0xB8 };
	group_tag gui_button_key_definition = { 'bkey', "gui_button_key_definition", 0x54 };
	group_tag crate = { 'bloc', "crate", 0x14 };
	group_tag gui_bitmap_widget_definition = { 'bmp3', "gui_bitmap_widget_definition", 0x60 };
	group_tag breakable_surface = { 'bsdt', "breakable_surface", 0x60 };
	group_tag collision_damage = { 'cddf', "collision_damage", 0x30 };
	group_tag cache_file_global_tags = { 'cfgt', "cache_file_global_tags", 0x10 };
	group_tag camera_fx_settings = { 'cfxs', "camera_fx_settings", 0x170 };
	group_tag chud_animation_definition = { 'chad', "chud_animation_definition", 0x5C };
	group_tag character = { 'char', "character", 0x1F8 };
	group_tag chud_definition = { 'chdt', "chud_definition", 0x18 };
	group_tag chud_globals_definition = { 'chgd', "chud_globals_definition", 0x2C0 };
	group_tag chocolate_mountain_new = { 'chmt', "chocolate_mountain_new", 0xC };
	group_tag cinematic = { 'cine', "cinematic", 0xB4 };
	group_tag cinematic_scene = { 'cisc', "cinematic_scene", 0x78 };
	group_tag cloth = { 'clwd', "cloth", 0x94 };
	group_tag camo = { 'cmoe', "camo", 0x3C };
	group_tag contrail_system = { 'cntl', "contrail_system", 0x14 };
	group_tag collision_model = { 'coll', "collision_model", 0x44 };
	group_tag color_table = { 'colo', "color_table", 0x10 };
	group_tag chud_widget_parallax_data = { 'cprl', "chud_widget_parallax_data", 0x10 };
	group_tag creature = { 'crea', "creature", 0x100 };
	group_tag cortana_effect_definition = { 'crte', "cortana_effect_definition", 0x80 };
	group_tag device_control = { 'ctrl', "device_control", 0x44 };
	group_tag decorator_set = { 'dctr', "decorator_set", 0x80 };
	group_tag decal_system = { 'decs', "decal_system", 0x24 };
	group_tag device = { 'devi', "device", 0x98 };
	group_tag rasterizer_cache_file_globals = { 'draw', "rasterizer_cache_file_globals", 0x10 };
	group_tag damage_response_definition = { 'drdf', "damage_response_definition", 0x18 };
	group_tag gui_datasource_definition = { 'dsrc', "gui_datasource_definition", 0x20 };
	group_tag effect = { 'effe', "effect", 0x70 };
	group_tag effect_globals = { 'effg', "effect_globals", 0x10 };
	group_tag effect_scenery = { 'efsc', "effect_scenery", 0xC };
	group_tag equipment = { 'eqip', "equipment", 0x1B0 };
	group_tag flock = { 'flck', "flock", 0x60 };
	group_tag material_effects = { 'foot', "material_effects", 0xC };
	group_tag forge_globals_definition = { 'forg', "forge_globals_definition", 0x90 };
	group_tag formation = { 'form', "formation", 0x18 };
	group_tag gfx_textures_list = { 'gfxt', "gfx_textures_list", 0x10 };
	group_tag giant = { 'gint', "giant", 0x28 };
	group_tag global_pixel_shader = { 'glps', "global_pixel_shader", 0x1C };
	group_tag global_vertex_shader = { 'glvs', "global_vertex_shader", 0x1C };
	group_tag multiplayer_variant_settings_interface_definition = { 'goof', "multiplayer_variant_settings_interface_definition", 0x10 };
	group_tag game_progression = { 'gpdt', "game_progression", 0x44 };
	group_tag gui_group_widget_definition = { 'grup', "gui_group_widget_definition", 0x60 };
	group_tag model = { 'hlmt', "model", 0x1B4 };
	group_tag input_globals = { 'inpg', "input_globals", 0x34 };
	group_tag item = { 'item', "item", 0xB4 };
	group_tag model_animation_graph = { 'jmad', "model_animation_graph", 0x104 };
	group_tag sandbox_text_value_pair_definition = { 'jmrq', "sandbox_text_value_pair_definition", 0xC };
	group_tag damage_effect = { 'jpt!', "damage_effect", 0xF4 };
	group_tag scenario_lightmap_bsp_data = { 'Lbsp', "scenario_lightmap_bsp_data", 0x1EC };
	group_tag lens_flare = { 'lens', "lens_flare", 0x9C };
	group_tag light = { 'ligh', "light", 0x94 };
	group_tag sound_looping = { 'lsnd', "sound_looping", 0x40 };
	group_tag gui_list_widget_definition = { 'lst3', "gui_list_widget_definition", 0x70 };
	group_tag leaf_system = { 'lswd', "leaf_system", 0x58 };
	group_tag light_volume_system = { 'ltvl', "light_volume_system", 0x14 };
	group_tag device_machine = { 'mach', "device_machine", 0x24 };
	group_tag globals = { 'matg', "globals", 0x608 };
	group_tag gui_model_widget_definition = { 'mdl3', "gui_model_widget_definition", 0x90 };
	group_tag ai_mission_dialogue = { 'mdlg', "ai_mission_dialogue", 0xC };
	group_tag muffin = { 'mffn', "muffin", 0x38 };
	group_tag render_model = { 'mode', "render_model", 0x1D0 };
	group_tag multiplayer_globals = { 'mulg', "multiplayer_globals", 0x18 };
	group_tag new_cinematic_lighting = { 'nclt', "new_cinematic_lighting", 0x1C };
	group_tag game_object = { 'obje', "game_object", 0x120 };
	group_tag particle_emitter_custom_points = { 'pecp', "particle_emitter_custom_points", 0x34 };
	group_tag podium_settings = { 'pdm!', "podium_settings", 0x3C };
	group_tag performance_throttles = { 'perf', "performance_throttles", 0x10 };
	group_tag physics_model = { 'phmo', "physics_model", 0x198 };
	group_tag pixel_shader = { 'pixl', "pixel_shader", 0x20 };
	group_tag cache_file_resource_layout_table = { 'play', "cache_file_resource_layout_table", 0x3C };
	group_tag particle_model = { 'pmdf', "particle_model", 0x90 };
	group_tag particle_physics = { 'pmov', "particle_physics", 0x2C };
	group_tag point_physics = { 'pphy', "point_physics", 0x40 };
	group_tag projectile = { 'proj', "projectile", 0x1AC };
	group_tag particle = { 'prt3', "particle", 0x1A0 };
	group_tag rasterizer_globals = { 'rasg', "rasterizer_globals", 0xBC };
	group_tag render_method = { 'rm  ', "render_method", 0x40 };
	group_tag shader_black = { 'rmbk', "shader_black", 0x4 };
	group_tag shader_custom = { 'rmcs', "shader_custom", 0x4 };
	group_tag shader_cortana = { 'rmct', "shader_cortana", 0x4 };
	group_tag shader_decal = { 'rmd ', "shader_decal", 0x0 };
	group_tag render_method_definition = { 'rmdf', "render_method_definition", 0x5C };
	group_tag shader_foliage = { 'rmfl', "shader_foliage", 0x4 };
	group_tag shader_halogram = { 'rmhg', "shader_halogram", 0x4 };
	group_tag render_method_option = { 'rmop', "render_method_option", 0x18 };
	group_tag shader = { 'rmsh', "shader", 0x10 };
	group_tag shader_screen = { 'rmss', "shader_screen", 0x14 };
	group_tag render_method_template = { 'rmt2', "render_method_template", 0x84 };
	group_tag shader_terrain = { 'rmtr', "shader_terrain", 0x1C };
	group_tag shader_water = { 'rmw ', "shader_water", 0x0 };
	group_tag shader_zonly = { 'rmzo', "shader_zonly", 0x8 };
	group_tag render_water_ripple = { 'rwrd', "render_water_ripple", 0x50 };
	group_tag scenario_lightmap = { 'sLdT', "scenario_lightmap", 0x50 };
	group_tag scenario_structure_bsp = { 'sbsp', "scenario_structure_bsp", 0x3AC };
	group_tag scenery = { 'scen', "scenery", 0x10 };
	group_tag gui_screen_widget_definition = { 'scn3', "gui_screen_widget_definition", 0xA8 };
	group_tag scenario = { 'scnr', "scenario", 0x824 };
	group_tag structure_design = { 'sddt', "structure_design", 0x44 };
	group_tag area_screen_effect = { 'sefc', "area_screen_effect", 0xC };
	group_tag sound_effect_collection = { 'sfx+', "sound_effect_collection", 0x10 };
	group_tag sound_global_propagation = { 'sgp!', "sound_global_propagation", 0x50 };
	group_tag shield_impact = { 'shit', "shield_impact", 0x1E4 };
	group_tag simulation_interpolation = { 'siin', "simulation_interpolation", 0xF4 };
	group_tag text_value_pair_definition = { 'sily', "text_value_pair_definition", 0x18 };
	group_tag gui_skin_definition = { 'skn3', "gui_skin_definition", 0x28 };
	group_tag sky_atm_parameters = { 'skya', "sky_atm_parameters", 0x4C };
	group_tag survival_mode_globals = { 'smdt', "survival_mode_globals", 0x48 };
	group_tag sound_classes = { 'sncl', "sound_classes", 0x10 };
	group_tag sound = { 'snd!', "sound", 0xD4 };
	group_tag sound_environment = { 'snde', "sound_environment", 0x50 };
	group_tag sound_mix = { 'snmx', "sound_mix", 0x80 };
	group_tag sound_dialogue_constants = { 'spk!', "sound_dialogue_constants", 0x30 };
	group_tag squad_template = { 'sqtm', "squad_template", 0x10 };
	group_tag sound_scenery = { 'ssce', "sound_scenery", 0x1C };
	group_tag style = { 'styl', "style", 0x5C };
	group_tag sound_ui_sounds = { 'sus!', "sound_ui_sounds", 0x10 };
	group_tag terminal = { 'term', "terminal", 0x140 };
	group_tag camera_track = { 'trak', "camera_track", 0x14 };
	group_tag texture_render_list = { 'trdf', "texture_render_list", 0x48 };
	group_tag gui_text_widget_definition = { 'txt3', "gui_text_widget_definition", 0x40 };
	group_tag dialogue = { 'udlg', "dialogue", 0x30 };
	group_tag sound_cache_file_gestalt = { 'ugh!', "sound_cache_file_gestalt", 0xDC };
	group_tag user_interface_sounds_definition = { 'uise', "user_interface_sounds_definition", 0x150 };
	group_tag multilingual_unicode_string_list = { 'unic', "multilingual_unicode_string_list", 0x50 };
	group_tag unit = { 'unit', "unit", 0x2C8 };
	group_tag vehicle = { 'vehi', "vehicle", 0x148 };
	group_tag v_files_list = { 'vfsl', "v_files_list", 0x20 };
	group_tag vision_mode = { 'vmdx', "vision_mode", 0x1A0 };
	group_tag vertex_shader = { 'vtsh', "vertex_shader", 0x20 };
	group_tag gui_widget_animation_collection_definition = { 'wacd', "gui_widget_animation_collection_definition", 0x280 };
	group_tag gui_widget_color_animation_definition = { 'wclr', "gui_widget_color_animation_definition", 0x24 };
	group_tag weapon = { 'weap', "weapon", 0x384 };
	group_tag game_engine_settings_definition = { 'wezr', "game_engine_settings_definition", 0x8C };
	group_tag gui_widget_animation_definition = { 'wgan', "gui_widget_animation_definition", 0x80 };
	group_tag user_interface_globals_definition = { 'wgtz', "user_interface_globals_definition", 0x50 };
	group_tag user_interface_shared_globals_definition = { 'wigl', "user_interface_shared_globals_definition", 0x3D0 };
	group_tag wind = { 'wind', "wind", 0x84 };
	group_tag gui_widget_position_animation_definition = { 'wpos', "gui_widget_position_animation_definition", 0x24 };
	group_tag gui_widget_rotation_animation_definition = { 'wrot', "gui_widget_rotation_animation_definition", 0x2C };
	group_tag gui_widget_scale_animation_definition = { 'wscl', "gui_widget_scale_animation_definition", 0x24 };
	group_tag gui_widget_sprite_animation_definition = { 'wspr', "gui_widget_sprite_animation_definition", 0x2C };
	group_tag gui_widget_texture_coordinate_animation_definition = { 'wtuv', "gui_widget_texture_coordinate_animation_definition", 0x2C };
	group_tag cache_file_resource_gestalt = { 'zone', "cache_file_resource_gestalt", 0x214 };

	std::vector<group_tag> GetVector()
	{
		return
		{
			sound_effect_template,
			achievements,
			ai_dialogue_globals,
			ai_globals,
			antenna,
			device_arg_device,
			armor,
			armor_sounds,
			beam_system,
			bink,
			biped,
			bitmap,
			gui_button_key_definition,
			crate,
			gui_bitmap_widget_definition,
			breakable_surface,
			collision_damage,
			cache_file_global_tags,
			camera_fx_settings,
			chud_animation_definition,
			character,
			chud_definition,
			chud_globals_definition,
			chocolate_mountain_new,
			cinematic,
			cinematic_scene,
			cloth,
			camo,
			contrail_system,
			collision_model,
			color_table,
			chud_widget_parallax_data,
			creature,
			cortana_effect_definition,
			device_control,
			decorator_set,
			decal_system,
			device,
			rasterizer_cache_file_globals,
			damage_response_definition,
			gui_datasource_definition,
			effect,
			effect_globals,
			effect_scenery,
			equipment,
			flock,
			material_effects,
			forge_globals_definition,
			formation,
			gfx_textures_list,
			giant,
			global_pixel_shader,
			global_vertex_shader,
			multiplayer_variant_settings_interface_definition,
			game_progression,
			gui_group_widget_definition,
			model,
			input_globals,
			item,
			model_animation_graph,
			sandbox_text_value_pair_definition,
			damage_effect,
			scenario_lightmap_bsp_data,
			lens_flare,
			light,
			sound_looping,
			gui_list_widget_definition,
			leaf_system,
			light_volume_system,
			device_machine,
			globals,
			gui_model_widget_definition,
			ai_mission_dialogue,
			muffin,
			render_model,
			multiplayer_globals,
			new_cinematic_lighting,
			game_object,
			particle_emitter_custom_points,
			podium_settings,
			performance_throttles,
			physics_model,
			pixel_shader,
			cache_file_resource_layout_table,
			particle_model,
			particle_physics,
			point_physics,
			projectile,
			particle,
			rasterizer_globals,
			render_method,
			shader_black,
			shader_custom,
			shader_cortana,
			shader_decal,
			render_method_definition,
			shader_foliage,
			shader_halogram,
			render_method_option,
			shader,
			shader_screen,
			render_method_template,
			shader_terrain,
			shader_water,
			shader_zonly,
			render_water_ripple,
			scenario_lightmap,
			scenario_structure_bsp,
			scenery,
			gui_screen_widget_definition,
			scenario,
			structure_design,
			area_screen_effect,
			sound_effect_collection,
			sound_global_propagation,
			shield_impact,
			simulation_interpolation,
			text_value_pair_definition,
			gui_skin_definition,
			sky_atm_parameters,
			survival_mode_globals,
			sound_classes,
			sound,
			sound_environment,
			sound_mix,
			sound_dialogue_constants,
			squad_template,
			sound_scenery,
			style,
			sound_ui_sounds,
			terminal,
			camera_track,
			texture_render_list,
			gui_text_widget_definition,
			dialogue,
			sound_cache_file_gestalt,
			user_interface_sounds_definition,
			multilingual_unicode_string_list,
			unit,
			vehicle,
			v_files_list,
			vision_mode,
			vertex_shader,
			gui_widget_animation_collection_definition,
			gui_widget_color_animation_definition,
			weapon,
			game_engine_settings_definition,
			gui_widget_animation_definition,
			user_interface_globals_definition,
			user_interface_shared_globals_definition,
			wind,
			gui_widget_position_animation_definition,
			gui_widget_rotation_animation_definition,
			gui_widget_scale_animation_definition,
			gui_widget_sprite_animation_definition,
			gui_widget_texture_coordinate_animation_definition,
			cache_file_resource_gestalt
		};

	}
	group_tag GetFirst() { return sound_effect_template; }
	group_tag GetLast() { return cache_file_resource_gestalt; }
} group_tags;

void PrintTagGroupEnum()
{
	auto group_tag_array = group_tags.GetVector();
	printf_s("\n/* This enum was auto-generated for use with IDA and Ghidra */\n");
	printf_s("enum e_tag_group\n");
	printf_s("{\n");
	for (auto t : group_tag_array)
		printf_s("    %s = 0x%X%s\n", t.name, t.group, (t.group != group_tags.GetLast().group ? "," : ""));
	printf_s("};\n\n");
}

void PrintTagGroup(uint32_t tag_group, uint16_t tag_index)
{
	auto group_tag_array = group_tags.GetVector();
	for (auto t : group_tag_array)
		if (tag_group == t.group)
			printf_s("0x%X, %s\n", tag_index, t.name);
}

uint8_t *globals_get_definition(bool *is_loaded)
{
	// make a global array of all these and create a function
	// to enumerate through and get the correct definition
	tag globals = { group_tags.globals, "globals\\globals", globals_tag };

	*is_loaded = true;
	if (!globals.IsLoaded())
		*is_loaded = false;

	return globals.GetDefinition();
}
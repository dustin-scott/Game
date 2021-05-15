/*
 * obj_model.h
 *
 *  Created on: Jan 12, 2013
 *      Author: Dustin Scott
 */

#ifndef OBJ_MODEL_H_
#define OBJ_MODEL_H_
#include <cstring>
#include <list>
#include <cstdlib>
	typedef bool obj_bool;
	typedef float obj_float;
	typedef unsigned char obj_char;
	typedef long unsigned int obj_unsigned_long_int;
	typedef struct _vertice
	{
			obj_float x;
			obj_float y;
			obj_float z;
			obj_float w;
	} obj_vertice;
	typedef struct _texture_coordinate
	{
			obj_float u;
			obj_float v;
			obj_float w;
	} obj_texture_coordinate;
	typedef struct _normal
	{
			obj_float i;
			obj_float j;
			obj_float k;
	} obj_normal;

	typedef struct _parameter_space_vertice
	{

	} obj_parameter_space_vertice;

	typedef struct _polygon_definition
	{
		obj_unsigned_long_int vertices_count;
		obj_vertice* vertices;
		obj_unsigned_long_int normals_count;
		obj_normal* normals;
		obj_unsigned_long_int texture_coordinates_count;
		obj_texture_coordinate* texture_coordinates;
	} obj_polygon;

	
	typedef struct _obj_mtl_color
	{
		//all values should be between 0.0f and 1.0f
		obj_float red;
		obj_float green;
		obj_float blue;
	} obj_mtl_color;
	typedef struct _obj_mtl_image_data
	{
			obj_char* path;
			obj_unsigned_long_int data_pointer;
	} obj_mtl_image_data;
	typedef struct _obj_material
	{
		obj_char* name;
		obj_mtl_color ambient;
		obj_mtl_color diffuse;
		obj_mtl_color specular;
		obj_mtl_color emission;
		obj_unsigned_long_int illumination;
		obj_float dissolve_factor;
		obj_float specular_exponent;
		obj_unsigned_long_int sharpness;
		obj_float index_of_refraction;

		obj_mtl_image_data map_ambient;
		obj_mtl_image_data map_diffuse;
		obj_mtl_image_data map_dissolve;
	} obj_material;

	typedef struct _material_group
	{
			obj_bool smoothing;
			obj_material* material;
			obj_unsigned_long_int draw_type;

			obj_unsigned_long_int polygons_count;
			obj_unsigned_long_int polygons_begin;
	} obj_material_group;
	typedef struct _group
	{
			obj_char* name;
			obj_unsigned_long_int material_groups_count;
			obj_unsigned_long_int material_groups_begin;
	} obj_group;

	typedef struct _obj
	{
			obj_char* name;
			obj_unsigned_long_int groups_begin; // beginning of groups
			obj_unsigned_long_int groups_count; // number of groups
	} obj_object;

	typedef struct _obj_model
	{
			obj_char* file_path;
			obj_unsigned_long_int objects_count;
			obj_unsigned_long_int vertices_count;
			obj_unsigned_long_int normals_count;
			obj_unsigned_long_int texture_coordinates_count;
			obj_unsigned_long_int materials_count;
			obj_unsigned_long_int material_groups_count;
			obj_unsigned_long_int groups_count;
			obj_unsigned_long_int polygons_count;
			obj_object* objects;
			obj_vertice* vertices;
			obj_normal* normals;
			obj_texture_coordinate* texture_coordinates;
			obj_material* materials;
			obj_material_group* material_groups;
			obj_polygon* polygons;
			obj_group* groups;
	} obj_model;

	obj_model* load_obj_file(const char* file_name);
	obj_model* create_test_obj();
	void delete_obj_model(obj_model* model);
#endif /* OBJ_MODEL_H_ */

/*
 * obj_model.c
 *
 *  Created on: Jan 12, 2013
 *      Author: Dustin Scott
 */
#include "obj_model.h"
#include <cstdio>

std::list<obj_char*> tokenize(obj_char* haystack, obj_char* separator)
{
	obj_char temp_haystack[strlen((char*)haystack)+1];
	strcpy((char*)&temp_haystack, (char*)haystack);
	std::list<obj_char*> pieces;

	obj_char* cur_tok = (obj_char*)strtok((char*)temp_haystack, (const char*)separator);
	obj_char* temp_tok = 0;
	while(cur_tok != 0)
	{
		temp_tok = new obj_char[strlen((char*)cur_tok)+1];
		strcpy((char*)temp_tok, (char*)cur_tok);
		pieces.push_back(temp_tok);
		cur_tok = (obj_char*)strtok(0, (const char*)separator);
	}

	return pieces;
}
std::list<obj_char*> explode(obj_char* haystack, obj_char* separator)
{
	int haystack_length = strlen((char*)haystack);
	int separator_length = strlen((char*)separator);

	obj_char temp_haystack[haystack_length+1];
	strcpy((char*)&temp_haystack, (char*)haystack);
	std::list<obj_char*> pieces;

	obj_char* cur_tok = &temp_haystack[0];
	obj_char* last_tok = &temp_haystack[0];
	obj_char* temp_tok = 0;
	int tok_length = 0;

	for(int i =0; i < haystack_length && cur_tok != 0; i++)
	{
		cur_tok = (obj_char*)strstr((char*)last_tok, (char*)separator);
		if(cur_tok)
		{
			tok_length = cur_tok - last_tok;
		}
		else
		{
			tok_length = strlen((char*)last_tok);
		}

		temp_tok = new obj_char[tok_length+1];
		strncpy((char*)temp_tok, (char*)last_tok, tok_length);
		temp_tok[tok_length] = '\0';
		pieces.push_back(temp_tok);

		if((tok_length+separator_length) > haystack_length-1)
		{
			//can't search farther if skipping the separator exceeds length
			break;
		}
		last_tok = cur_tok+separator_length;
	}

	return pieces;
}

void get_line(obj_char* buffer, FILE* model_file)
{
	unsigned int i = 0;
	for(obj_char cur = fgetc(model_file); cur != '\n' && !feof(model_file); cur = fgetc(model_file))
	{
		//pfft \r
		if(cur != '\r')
		{
			buffer[i] = cur;
			i++;
		}
	}
	buffer[i] = '\0'; // null terminated strings
}

obj_char* convert_slashes(obj_char* buffer)
{
	obj_unsigned_long_int i = 0;
	obj_unsigned_long_int j = 0;

	//include the null character
	obj_unsigned_long_int string_length = strlen((char*)buffer);
	obj_char* return_value = new obj_char[string_length+1];

	obj_char last_char = '\0';
	bool check = 0;
	for(i = 0, j = 0; j < string_length; j++)
	{
		check = (buffer[j] == '\\' || buffer[j] == '/');
		check = check && (last_char != '\\' && last_char != '/');
		if(check)
		{
			return_value[i] = '/';
			i++;
		}
		if(!check && (buffer[j] != '\\' && buffer[j] != '/'))
		{
			return_value[i] = buffer[j];
			i++;
		}
		last_char = buffer[j];
	}
	return_value[i] = '\0'; // string may be shorter now, null terminate

	return return_value;
}

obj_char* normalize_path(obj_char* path)
{
	obj_char* file_path = convert_slashes(path);
	obj_unsigned_long_int i = 0;
	obj_unsigned_long_int j = 0;

	//include the null character
	obj_unsigned_long_int model_file_length = strlen((char*)file_path)+1;

	obj_char* file_directory = new obj_char[model_file_length];
	obj_char last_char = '\0';
	bool check = 0;
	for(i = 0, j = 0; j < model_file_length; j++)
	{
		check = (file_path[j] == '\\' || file_path[j] == '/');
		check = check && (last_char != '\\' && last_char != '/');
		if(check || (file_path[j] != '\\' && file_path[j] != '/'))
		{
			file_directory[i] = file_path[j];
			i++;
		}
		last_char = file_path[j];
	}

	delete[] file_path;
	return file_directory;
}
obj_char* get_file_directory(obj_char* file_path)
{
	obj_unsigned_long_int i = 0;
	obj_unsigned_long_int j = 0;

	//include the null character
	obj_unsigned_long_int model_file_length = strlen((char*)file_path)+1;

	obj_char* file_directory = new obj_char[model_file_length];
	obj_unsigned_long_int last_slash = 0;
	obj_char last_char = '\0';
	bool check = 0;
	for(i = 0, j = 0; j < model_file_length; j++)
	{
		check = (file_path[j] == '\\' || file_path[j] == '/');
		check = check && (last_char != '\\' && last_char != '/');
		//check = check || (file_path[j] != '\\' && file_path[j] != '/');
		if(check)
		{
			last_slash = i;
		}
		if(check || (file_path[j] != '\\' && file_path[j] != '/'))
		{
			file_directory[i] = file_path[j];
			i++;
		}
		last_char = file_path[j];
	}

	file_directory[last_slash+1] = '\0'; // terminate string after last slash
	return file_directory;
}

bool str_eq(const obj_char* str1, const obj_char* str2)
{
	bool equal = (str1 == str2);

	if(!equal)
	{
		if(str1 != 0 && str2 != 0)
		{
			equal = (strcoll((char*)str1,(char*)str2) == 0);
		}
	}

	return equal;
}

const obj_char* NEW_MATERIAL = (obj_char*)"newmtl";
const obj_char* SPECULAR_EXPONENT = (obj_char*)"Ns";
const obj_char* INDEX_OF_REFRACTION = (obj_char*)"Ni";
const obj_char* COLOR_AMBIENT = (obj_char*)"Ka";
const obj_char* COLOR_DIFFUSE = (obj_char*)"Kd";
const obj_char* COLOR_SPECULAR = (obj_char*)"Ks";
const obj_char* COLOR_EMISSION = (obj_char*)"Ke";
const obj_char* DISSOLVE_FACTOR = (obj_char*)"d";
const obj_char* TRANSMISSION_FILTER = (obj_char*)"Tf";
const obj_char* ILLUMINATION = (obj_char*)"illum";
const obj_char* MAP_AMBIENT = (obj_char*)"map_Ka";
const obj_char* MAP_DIFFUSE = (obj_char*)"map_Kd";
const obj_char* MAP_SPECULAR = (obj_char*)"map_Ks";
const obj_char* MAP_SCALAR = (obj_char*)"map_Ns";
const obj_char* MAP_DISSOLVE = (obj_char*)"map_d";
const obj_char* MAP_ANTI_ALIASING_TEXTURES = (obj_char*)"map_aat";

void count_materials(obj_model* model, obj_char* material_path)
{
	obj_char* file_directory = get_file_directory(model->file_path);

	obj_char relative_material_path[strlen((char*)file_directory)+strlen((char*)material_path)+1];

	strcpy((char*)relative_material_path, (char*)file_directory);
	delete[] file_directory;

	strcat((char*)relative_material_path, (char*)material_path);

	printf("%s\n", relative_material_path);

	FILE* material_file;
	obj_char line[100];

	obj_char* cur;

	std::list<obj_char*> pieces;

	material_file = fopen((char*)relative_material_path , "r");
	if (material_file == NULL)
	{
		perror("Error opening file");
	}
	else
	{
		while(!feof(material_file))
		{
			get_line(line, material_file);
			pieces = tokenize(&line[0], (obj_char*)" ");
			cur = pieces.front();
			if(str_eq(cur, NEW_MATERIAL))
			{
				model->materials_count++;
			}
			while(!pieces.empty())
			{
				delete[] cur;
				pieces.pop_front();
				cur = pieces.front();
			}
		}
		fclose(material_file);
	}
}
void parse_material(obj_model* model, obj_char* material_path)
{
	obj_char* file_directory = get_file_directory(model->file_path);

	obj_char relative_material_path[strlen((char*)file_directory)+strlen((char*)material_path)+1];

	strcpy((char*)relative_material_path, (char*)file_directory);
	delete[] file_directory;

	strcat((char*)relative_material_path, (char*)material_path);

	printf("%s\n", relative_material_path);

	FILE* material_file;
	obj_char line[100];

	obj_char* cur;

	std::list<obj_char*> pieces;

	material_file = fopen((char*)relative_material_path , "r");
	if (material_file == NULL)
	{
		perror("Error opening file");
	}
	else
	{
		obj_material* cur_material;
		obj_unsigned_long_int material_iterator = 0;
		while(!feof(material_file))
		{
			get_line(line, material_file);
			pieces = tokenize(&line[0], (obj_char*)" ");
			if(pieces.size() > 0)
			{
				cur = pieces.front();
				pieces.pop_front();
				if(str_eq(cur, NEW_MATERIAL))
				{
					cur_material = &model->materials[material_iterator];
					material_iterator++;
					//new material name
					cur_material->name = new obj_char[strlen((char*)pieces.front())+1];
					strcpy((char*)cur_material->name, (char*)pieces.front());
				}
				else
				{
					//processing something for current material
					if(str_eq(cur, SPECULAR_EXPONENT))
					{
						cur_material->specular_exponent = strtof((char*)pieces.front(), 0);
					}
					else if(str_eq(cur, COLOR_AMBIENT))
					{
						if(pieces.size() == 3)
						{
							cur_material->ambient.red = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();

							cur_material->ambient.green = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();

							cur_material->ambient.blue = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();
						}
						else
						{
							perror("\nMalformed material for Ka\n");
							exit(1);
						}
					}
					else if(str_eq(cur, COLOR_DIFFUSE))
					{
						if(pieces.size() == 3)
						{
							cur_material->diffuse.red = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();

							cur_material->diffuse.green = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();

							cur_material->diffuse.blue = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();
						}
						else
						{
							perror("\nMalformed material for Kd\n");
							exit(1);
						}
					}
					else if(str_eq(cur, COLOR_SPECULAR))
					{
						if(pieces.size() == 3)
						{
							cur_material->specular.red = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();

							cur_material->specular.green = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();

							cur_material->specular.blue = strtof((char*)pieces.front(), 0);
							delete[] pieces.front();
							pieces.pop_front();
						}
						else
						{
							perror("\nMalformed material for Ks\n");
							exit(1);
						}
					}
					else if(str_eq(cur, INDEX_OF_REFRACTION))
					{
						cur_material->index_of_refraction = strtof((char*)pieces.front(), 0);
					}
					else if(str_eq(cur, DISSOLVE_FACTOR))
					{
						if(pieces.front()[0] != '-')
						{
							if(pieces.size() == 1)
							{
								cur_material->dissolve_factor = strtof((char*)pieces.front(), 0);
							}
							else
							{
								perror("\nMalformed dissolve factor\n");
								exit(1);
							}
						}
						else
						{
							perror("\nParser does not support dissolve parameters\n");
							exit(1);
						}
					}
					else if(str_eq(cur, ILLUMINATION))
					{
						if(pieces.size() == 1)
						{
							cur_material->illumination =  strtoul((char *)pieces.front(), 0, 0);
						}
						else
						{
							perror("\nInvalid illumination specification\n");
							exit(1);
						}
					}
					else if
					(
							str_eq(cur, MAP_AMBIENT)
							|
							str_eq(cur, MAP_DIFFUSE)
							|
							str_eq(cur, MAP_DISSOLVE)
					)
					{
						if(pieces.size() == 1)
						{
							char* front = (char*)pieces.front();
							obj_char first = front[0];
							obj_char* image_directory = 0;
							if
							(
								first != '/'
								&&
								first != '\\'
								&&
								strstr(front, ":") == 0
							)
							{
								obj_char* parent_dir = get_file_directory(model->file_path);
								obj_char* full_path = new obj_char[strlen((char*)parent_dir)+strlen(front)+1];
								strcpy((char*)full_path, (char*)parent_dir);
								strcat((char*)full_path, front);
								image_directory = normalize_path(full_path);
								delete[] parent_dir;
								delete[] full_path;
							}
							else
							{
								image_directory = normalize_path(pieces.front());
							}
							obj_char* path = new obj_char[strlen((char*)image_directory)+1];

							strcpy((char*)path, (char*)image_directory);

							if(str_eq(cur, MAP_AMBIENT))
							{
								cur_material->map_ambient.path = path;
							}
							else if(str_eq(cur, MAP_DIFFUSE))
							{
								cur_material->map_diffuse.path = path;
							}
							else if(str_eq(cur, MAP_DISSOLVE))
							{
								cur_material->map_dissolve.path = path;
							}

							delete[] image_directory;
						}
						else
						{
							perror("\narguments not supported\n");
							exit(1);
						}
					}
				}
				while(!pieces.empty())
				{
					delete[] cur;
					pieces.pop_front();
					cur = pieces.front();
				}
			}
		}
		fclose(material_file);
	}
}

const obj_char* OBJ_VERTICE = (obj_char*)"v";
const obj_char* OBJ_TEXTURE_COORDINATE =  (obj_char*)"vt";
const obj_char* OBJ_SMOOTHING = (obj_char*)"s";
const obj_char* OBJ_FACE =  (obj_char*)"f";
const obj_char* OBJ_OBJECT =  (obj_char*)"o";
const obj_char* OBJ_NORMAL =  (obj_char*)"vn";
const obj_char* OBJ_MATERIAL_LIBRARY =  (obj_char*)"mtllib";
const obj_char* OBJ_GROUP = (obj_char*)"g";
const obj_char* OBJ_USE_MATERIAL = (obj_char*)"usemtl";
const obj_char OBJ_COMMENT = '#';

obj_group* find_group(obj_model* model, obj_object* object, obj_char* group_name)
{
	obj_group* found_group = 0;
	obj_unsigned_long_int i = 0;

	for(i = object->groups_begin; i < object->groups_begin+object->groups_count; i++)
	{
		if(str_eq(model->groups[i].name, group_name))
		{
			found_group = &model->groups[i];
			break;
		}
	}

	return found_group;
}

void count_attributes(obj_model* model, std::list<obj_char*>* pieces)
{
	obj_char* first = pieces->front();
	pieces->pop_front();

	if(str_eq(first,OBJ_OBJECT))
	{
		model->objects_count++;
		//model->groups_count++;
		//model->material_groups_count++;

		obj_char* name = 0;

		if(pieces->size() == 1)
		{
			name = pieces->front();
			pieces->pop_front();
		}

		obj_object* old_objects = model->objects;
		model->objects = new obj_object[model->objects_count];

		if(model->objects_count > 1)
		{
			obj_unsigned_long_int j = 0;

			for(j = 0; j < model->objects_count-1; j++)
			{
				model->objects[j] = old_objects[j];
			}

			delete[] old_objects;
		}

		model->objects[model->objects_count-1].groups_begin = model->groups_count;
		model->objects[model->objects_count-1].groups_count = 1;
		model->objects[model->objects_count-1].name = name;

		model->groups_count++;
		model->material_groups_count++;
		obj_group* old_groups = model->groups;
		model->groups = new obj_group[model->groups_count];
		if(model->groups_count > 1)
		{
			obj_unsigned_long_int j = 0;
			for(j = 0; j < model->groups_count-1; j++)
			{
				model->groups[j] = old_groups[j];
			}
			delete[] old_groups;
		}
		model->groups[model->groups_count-1].material_groups_begin = model->material_groups_count;
		model->groups[model->groups_count-1].material_groups_count = 1;
		model->groups[model->groups_count-1].name = 0;
	}
	else if(str_eq(first, OBJ_USE_MATERIAL))
	{
		model->material_groups_count++;
	}
	else if(str_eq(first, OBJ_GROUP))
	{
		obj_char* name = 0;
		//printf("\nname: %s\n", name);

		//pieces->push_front(0);
		while(!pieces->empty())
		{
			//printf("\nstart while: %i\n", pieces->size());
			name = pieces->front();
			pieces->pop_front();

			if(find_group(model, &model->objects[model->objects_count-1], name) == 0)
			{
				model->objects[model->objects_count-1].groups_count++;
				model->groups_count++;
				model->material_groups_count++;
			//	printf("\nhere\n");
				obj_group* old_groups = model->groups;
			//	printf("\nhere2\n");
				model->groups = new obj_group[model->groups_count];
				if(model->groups_count > 1)
				{
					obj_unsigned_long_int j = 0;
					for(j = 0; j < model->groups_count-1; j++)
					{
						model->groups[j] = old_groups[j];
					}
					delete[] old_groups;
				}
				model->groups[model->groups_count-1].material_groups_begin = 0;
				model->groups[model->groups_count-1].material_groups_count = 0;
				model->groups[model->groups_count-1].name = name;
			}
			//printf("\nend loop\n");
		}
	}
	else if(str_eq(first,OBJ_VERTICE))
	{
		model->vertices_count++;
	}
	else if(str_eq(first,OBJ_TEXTURE_COORDINATE))
	{
		model->texture_coordinates_count++;
	}
	else if(str_eq(first,OBJ_FACE))
	{
		model->polygons_count++;
	}
	else if(str_eq(first,OBJ_NORMAL))
	{
		model->normals_count++;
	}
	else if(str_eq(first, OBJ_MATERIAL_LIBRARY))
	{
		obj_char* material_path= pieces->front();
		pieces->pop_front();

		count_materials(model, material_path);
		delete[] material_path;
	}
	else
	{
		//printf("%s\n", pieces.front());
	}
}

void set_primary_attributes(obj_model* model, FILE* model_file)
{
	rewind(model_file);

	std::list<obj_char*> pieces;
	obj_char line[100];
	obj_char* first = 0;

	obj_unsigned_long_int object_iterator = 0;
	obj_unsigned_long_int group_iterator = 0;
	obj_unsigned_long_int material_group_iterator = 0;
	obj_unsigned_long_int vertice_iterator = 0;
	obj_unsigned_long_int normal_iterator = 0;
	obj_unsigned_long_int texture_coordinate_iterator = 0;

	obj_group* cur_group_collection[model->groups_count];
	cur_group_collection[0] = &model->groups[group_iterator];
	obj_unsigned_long_int cur_group_collection_length = 1;

	//second_pass
	while(!feof(model_file))
	{
		get_line(&line[0], model_file);

		if(line[0] != OBJ_COMMENT)
		{
			pieces = tokenize(&line[0], (obj_char*)" ");

			if(!pieces.empty())
			{
				first = pieces.front();
				pieces.pop_front();

				if(str_eq(first,OBJ_OBJECT))
				{
					object_iterator++;
					//printf("Obj name: %s\n",model->objects[object_iterator].name);
				}
				else if(str_eq(first, OBJ_GROUP))
				{
					cur_group_collection_length = 1;
					obj_char* name = 0;
					if(pieces.size() > 0)
					{
						obj_group* found_group = 0;
						while(!pieces.empty())
						{
							name = pieces.front();
							pieces.pop_front();
							found_group = find_group(model, &model->objects[object_iterator], name);
							if(found_group != 0)
							{
								cur_group_collection[cur_group_collection_length] = found_group;
								cur_group_collection_length++;
							}
							else
							{
								obj_unsigned_long_int j = 0;
								for(j = 0; j < model->groups_count; j++)
								{
									printf("\ngroup name: %s\n", model->groups[j].name);
								}
								printf("\nobject groups\n");
								for(j = model->objects[object_iterator].groups_begin; j <  model->objects[object_iterator].groups_begin+model->objects[object_iterator].groups_count; j++)
								{
									printf("\ngroup name: %s\n", model->groups[j].name);
								}
								perror("\ngroup should of been allocated already\n");
								exit(1);
							}
							delete[] name;
						}
					}

					material_group_iterator++;
					obj_unsigned_long_int j = 0;
					for(j = 0; j < cur_group_collection_length; j++)
					{
						cur_group_collection[j]->material_groups_count++;
					}
				}
				else if(str_eq(first, OBJ_USE_MATERIAL))
				{
					material_group_iterator++;

					obj_unsigned_long_int j = 0;
					for(j = 0; j < cur_group_collection_length; j++)
					{
						cur_group_collection[j]->material_groups_count++;
					}
				}
				else if(str_eq(first,OBJ_VERTICE))
				{
					if(pieces.size() >= 3)
					{
						obj_vertice* temp_vertice = &model->vertices[vertice_iterator];

						temp_vertice->x = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						temp_vertice->y = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						temp_vertice->z = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						if(!pieces.empty())
						{
							temp_vertice->w = strtof((char*)pieces.front(), 0);

							delete[] pieces.front();
							pieces.pop_front();
						}
						else
						{
							temp_vertice->w = 1.0f;
						}

						vertice_iterator++;
					}
					else
					{
						char error[100];
						sprintf(&error[0], "file malformed: %u elements", pieces.size());

						perror(error);
						exit(1);
					}
				}
				else if(str_eq(first,OBJ_NORMAL))
				{
					if(pieces.size() == 3)
					{
						obj_normal* temp_normal = &model->normals[normal_iterator];

						temp_normal->i = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						temp_normal->j = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						temp_normal->k = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						normal_iterator++;
					}
					else
					{
						char error[100];
						sprintf(&error[0], "file malformed: %u elements", pieces.size());

						perror(error);
						exit(1);
					}
				}
				else if(str_eq(first,OBJ_TEXTURE_COORDINATE))
				{
					if(pieces.size() >= 1)
					{

						obj_texture_coordinate* temp_coordinate = &model->texture_coordinates[texture_coordinate_iterator];

						temp_coordinate->u = strtof((char*)pieces.front(), 0);

						delete[] pieces.front();
						pieces.pop_front();

						if(!pieces.empty())
						{
							temp_coordinate->v = strtof((char*)pieces.front(), 0);

							delete[] pieces.front();
							pieces.pop_front();
						}
						else
						{
							temp_coordinate->v = 0.0f;
						}

						if(!pieces.empty())
						{
							temp_coordinate->w = strtof((char*)pieces.front(), 0);

							delete[] pieces.front();
							pieces.pop_front();
						}
						else
						{
							temp_coordinate->w = 0.0f;
						}

						texture_coordinate_iterator++;
					}
					else
					{
						char error[100];
						sprintf(&error[0], "file malformed: %u elements", pieces.size());

						perror(error);
						exit(1);
					}
				}
				else if(str_eq(first, OBJ_MATERIAL_LIBRARY))
				{
					obj_char* material_path = pieces.front();
					pieces.pop_front();

					parse_material(model, material_path);

					delete[] material_path;
				}

				delete[] first;
				while(!pieces.empty())
				{
					delete[] pieces.front();
					pieces.pop_front();
				}
			}
		}
	}
	object_iterator++; // account for default object
	if((object_iterator ^ model->objects_count) |
		(vertice_iterator ^ model->vertices_count) |
		(normal_iterator ^ model->normals_count) |
		(texture_coordinate_iterator ^ model->texture_coordinates_count))
	{
		printf("\nobject_iterator: %lu, objects_count: %lu\n", object_iterator, model->objects_count);
		perror("\nData loss / malformed elements during second pass\n");
		exit(1);
	}
}
void set_derived_attributes(obj_model* model, FILE* model_file)
{
	rewind(model_file);

	std::list<obj_char*> pieces;
	std::list<obj_char*> polygon_chunk_pieces;
	obj_char line[100];
	obj_char* first = 0;

	obj_unsigned_long_int object_iterator = 0;
	obj_unsigned_long_int group_iterator = 0;
	obj_unsigned_long_int material_group_iterator = 0;
	obj_unsigned_long_int polygon_iterator = 0;

	obj_object* cur_object = &model->objects[object_iterator];
	obj_group* cur_group = &model->groups[group_iterator];
	obj_material_group* cur_material_group = &model->material_groups[material_group_iterator];

	obj_unsigned_long_int i = 0;

	//third_pass
	while(!feof(model_file))
	{
		get_line(line, model_file);

		if(line[0] != OBJ_COMMENT)
		{
			pieces = tokenize(&line[0], (obj_char*)" ");
			if(!pieces.empty())
			{
				first = pieces.front();
				pieces.pop_front();
				if(str_eq(first,OBJ_OBJECT))
				{
					object_iterator++;
					cur_object = &model->objects[object_iterator];

					group_iterator++;
					cur_object->groups_begin = group_iterator;
					cur_object->groups_count = 1;

					cur_group = &model->groups[group_iterator];

					material_group_iterator++;
					//printf("\nmaterial_group_iterator: %lu\n", material_group_iterator);
					cur_group->material_groups_begin = material_group_iterator;
					cur_group->material_groups_count = 1;

					cur_material_group = &model->material_groups[material_group_iterator];
					cur_material_group->polygons_begin = polygon_iterator;
					cur_material_group->polygons_count = 0;

				}
				else if(str_eq(first, OBJ_GROUP))
				{
					group_iterator++;
					cur_group = &model->groups[group_iterator];

					material_group_iterator++;
					//printf("\nmaterial_group_iterator: %lu\n", material_group_iterator);
					cur_group->material_groups_begin = material_group_iterator;
					cur_group->material_groups_count = 1;

					cur_material_group = &model->material_groups[material_group_iterator];

					cur_material_group->material = 0;
					cur_material_group->polygons_begin = polygon_iterator;
					cur_material_group->polygons_count = 0;
				}
				else if(str_eq(first, OBJ_USE_MATERIAL))
				{
					cur_group->material_groups_count++;
					material_group_iterator++;
					//printf("\nmaterial_group_iterator: %lu\n", material_group_iterator);
					cur_material_group = &model->material_groups[material_group_iterator];

					obj_char* material_name = pieces.front();
					obj_unsigned_long_int i = 0;
					obj_material* found_material = 0;
					for(i = 0; i < model->materials_count; i++)
					{
						if(str_eq(model->materials[i].name, material_name))
						{
							found_material = &model->materials[i];
							break;
						}
					}
					if(found_material == 0)
					{
						char error[100];
						sprintf(&error[0], "\nCould not find material: %s\n", material_name);
						perror(&error[0]);
						exit(1);
					}

					cur_material_group->material = found_material;
					cur_material_group->polygons_begin = polygon_iterator;
					cur_material_group->polygons_count = 0;

				}
				else if(str_eq(first,OBJ_SMOOTHING))
				{
					if(pieces.size() == 1)
					{
						cur_material_group->smoothing = strtoul((char *)pieces.front(), 0, 0) > 0;
					}
					else
					{
						perror("\nmalformed smoothing definition\n");
						exit(1);
					}
				}
				else if(str_eq(first,OBJ_FACE))
				{
					if(pieces.size() >= 3)
					{
						obj_polygon* temp_polygon = &model->polygons[polygon_iterator];

						obj_unsigned_long_int polygon_vertice_count = 0;
						obj_unsigned_long_int polygon_normal_count = 0;
						obj_unsigned_long_int polygon_texture_coordinate_count = 0;

						obj_unsigned_long_int token_length = 0;
						obj_unsigned_long_int token_value = 0;
						obj_char* token = 0;

						for(std::list<obj_char*>::iterator cur_segment = pieces.begin(); cur_segment != pieces.end(); cur_segment++)
						{
							polygon_chunk_pieces = explode((*cur_segment), (obj_char*)"/");
							if(polygon_chunk_pieces.size() > 0)
							{
								token = polygon_chunk_pieces.front();
								token_length = strlen((char*)token);
								if(token_length > 0)
								{
									token_value = strtoul((char *)token, 0, 0);
									if(token_value > 0 && token_value <= model->vertices_count)
									{
										polygon_vertice_count++;
									}
									else
									{
										perror("\npolygon vertice that is out of range was specified\n");
										exit(1);
									}
									delete[] polygon_chunk_pieces.front();
									polygon_chunk_pieces.pop_front();
								}
								else
								{
									perror("\nMalformed polygon, no vertice defined\n");
									exit(1);
								}

								if(!polygon_chunk_pieces.empty())
								{
									token = polygon_chunk_pieces.front();
									token_length = strlen((char*)token);

									if(token_length > 0)
									{
										token_value = strtoul((char *)token, 0, 0);
										if(token_value > 0 && token_value <= model->texture_coordinates_count)
										{
											polygon_texture_coordinate_count++;
										}
										else
										{
											perror("\npolygon texture coordinate that is out of range was specified\n");
											exit(1);
										}
										delete[] polygon_chunk_pieces.front();
										polygon_chunk_pieces.pop_front();
									}
								}

								if(!polygon_chunk_pieces.empty())
								{
									token = polygon_chunk_pieces.front();
									token_length = strlen((char*)token);

									if(token_length > 0)
									{
										if(token_value > 0 && token_value <= model->normals_count)
										{
											polygon_normal_count++;
										}
										else
										{
											perror("\npolygon normal that is out of range was specified\n");
											exit(1);
										}
										delete[] polygon_chunk_pieces.front();
										polygon_chunk_pieces.pop_front();
									}
								}
							}
							else
							{
								perror("\nmalformed polygon definition\n");
								exit(1);
							}
						}

						temp_polygon->vertices_count = polygon_vertice_count;
						temp_polygon->texture_coordinates_count = polygon_texture_coordinate_count;
						temp_polygon->normals_count = polygon_normal_count;

						temp_polygon->vertices = new obj_vertice[polygon_vertice_count];
						temp_polygon->texture_coordinates = new obj_texture_coordinate[polygon_texture_coordinate_count];
						temp_polygon->normals = new obj_normal[polygon_normal_count];

						obj_unsigned_long_int temp_polygon_vertice_iterator = 0;
						obj_unsigned_long_int temp_polygon_texture_coordinate_iterator = 0;
						obj_unsigned_long_int temp_polygon_normal_iterator = 0;
						//printf("\nf: ");
						for(i = 0; !pieces.empty(); i++)
						{
							polygon_chunk_pieces = explode(pieces.front(), (obj_char*)"/");
							if(polygon_chunk_pieces.size() > 0)
							{
								token = polygon_chunk_pieces.front();
								token_length = strlen((char*)token);
								if(token_length > 0)
								{
									token_value = strtoul((char *)token, 0, 0);
									//printf("%lu", token_value);
									if(token_value > 0 && token_value <= model->vertices_count)
									{
										temp_polygon->vertices[temp_polygon_vertice_iterator].w = model->vertices[token_value-1].w;
										temp_polygon->vertices[temp_polygon_vertice_iterator].x = model->vertices[token_value-1].x;
										temp_polygon->vertices[temp_polygon_vertice_iterator].y = model->vertices[token_value-1].y;
										temp_polygon->vertices[temp_polygon_vertice_iterator].z = model->vertices[token_value-1].z;

										temp_polygon_vertice_iterator++;
									}
									else
									{
										perror("\npolygon vertice that is out of range was specified\n");
										exit(1);
									}
								}
								else
								{
									perror("\nMalformed polygon, no vertice defined\n");
									exit(1);
								}

								delete[] polygon_chunk_pieces.front();
								polygon_chunk_pieces.pop_front();

								if(!polygon_chunk_pieces.empty())
								{
									token = polygon_chunk_pieces.front();
									token_length = strlen((char*)token);
									if(token_length > 0)
									{
										token_value = strtoul((char *)token, 0, 0);
										//printf("/%lu", token_value);
										if(token_value > 0 && token_value <= model->texture_coordinates_count)
										{
											temp_polygon->texture_coordinates[temp_polygon_texture_coordinate_iterator].u = model->texture_coordinates[token_value-1].u;
											temp_polygon->texture_coordinates[temp_polygon_texture_coordinate_iterator].v = model->texture_coordinates[token_value-1].v;
											temp_polygon->texture_coordinates[temp_polygon_texture_coordinate_iterator].w = model->texture_coordinates[token_value-1].w;

											temp_polygon_texture_coordinate_iterator++;
										}
										else
										{
											perror("\nface texture coordinate that is out of range was specified\n");
											exit(1);
										}
									}

									delete[] polygon_chunk_pieces.front();
									polygon_chunk_pieces.pop_front();
								}

								if(!polygon_chunk_pieces.empty())
								{
									token = polygon_chunk_pieces.front();
									token_length = strlen((char*)token);
									if(token_length > 0)
									{
										token_value = strtoul((char *)token, 0, 0);
										//printf("/%lu", token_value);
										if(token_value > 0 && token_value <= model->normals_count)
										{
											temp_polygon->normals[temp_polygon_normal_iterator].i = model->normals[token_value-1].i;
											temp_polygon->normals[temp_polygon_normal_iterator].j = model->normals[token_value-1].j;
											temp_polygon->normals[temp_polygon_normal_iterator].k = model->normals[token_value-1].k;

											temp_polygon_normal_iterator++;
										}
										else
										{
											perror("\nface normal that is out of range was specified\n");
											exit(1);
										}
									}
									else
									{
										printf("Normal value zero\n");
									}
									delete[] polygon_chunk_pieces.front();
									polygon_chunk_pieces.pop_front();
								}
							}
							else
							{
								perror("\nmalformed polygon definition\n");
								exit(1);
							}

							delete[] pieces.front();
							pieces.pop_front();
							//printf(" ");
						}

						cur_material_group->polygons_count++;
						polygon_iterator++;
						//printf("\n");
					}
				}
/*
				if(material_group_iterator == 14)
				{
					printf("\n%s\n", first);
					printf("\npolygon iterator: %lu\n", polygon_iterator);
					printf("\npolygon begin: %lu\n", cur_material_group->polygons_begin);
					printf("\npolgon count: %lu\n", cur_material_group->polygons_count);
					exit(1);
				}*/
				delete[] first;
				while(!pieces.empty())
				{
					delete[] pieces.front();
					pieces.pop_front();
				}
			}
		}
	}
}
void parse_obj_file(obj_model* model, FILE* model_file, void (*call_back)(obj_model* model, std::list<obj_char*>* pieces))
{
	rewind(model_file);

	std::list<obj_char*> pieces;

	obj_char line[100];

	//third_pass
	while(!feof(model_file))
	{
		get_line(line, model_file);

		if(line[0] != OBJ_COMMENT)
		{
			pieces = tokenize(&line[0], (obj_char*)" ");

			if(!pieces.empty())
			{
				//printf("%s\n", &line[0]);
				(*call_back)(model, &pieces);
				while(!pieces.empty())
				{
					delete[] pieces.front();
					pieces.pop_front();
				}
			}
		}
	}
}
void count_and_allocate(obj_model* model, FILE* model_file)
{
	model->objects_count = 1;
	model->objects = new obj_object[model->objects_count];

	model->groups_count = 1;
	model->groups = new obj_group[model->groups_count];

	model->material_groups_count = 0;
	model->materials_count = 0;

	model->vertices_count = 0;
	model->polygons_count = 0;
	model->texture_coordinates_count = 0;
	model->normals_count = 0;

	model->objects[model->objects_count-1].groups_begin = 0;
	model->objects[model->objects_count-1].groups_count = 1;
	model->objects[model->objects_count-1].name = 0;

	model->groups[model->groups_count-1].material_groups_begin = 0;
	model->groups[model->groups_count-1].material_groups_count = 0;
	model->groups[model->groups_count-1].name = 0;

	parse_obj_file(model, model_file, count_attributes);

	printf("\ncompleted first allocation\n");

	printf("vertices: %lu\n",model->vertices_count);
	printf("polygons: %lu\n", model->polygons_count);
	printf("objects: %lu\n", model->objects_count);
	printf("texture coordinate count: %lu\n", model->texture_coordinates_count);
	printf("materials : %lu\n", model->materials_count);

	printf("\nobjects_count: %lu\n", model->objects_count);
	printf("\ngroups_count: %lu\n", model->groups_count);
	printf("\nmaterial_groups_count: %lu\n", model->material_groups_count);

	//model->objects = new obj_object[model->objects_count];
	//model->groups = new obj_group[model->groups_count];
	model->material_groups = new obj_material_group[model->material_groups_count];

	model->vertices = new obj_vertice[model->vertices_count];
	model->polygons = new obj_polygon[model->polygons_count];
	model->texture_coordinates = new obj_texture_coordinate[model->texture_coordinates_count];
	model->normals = new obj_normal[model->normals_count];
	model->materials = new obj_material[model->materials_count];

	obj_unsigned_long_int i = 0;

	for(i = 0; i < model->material_groups_count; i++)
	{
		model->material_groups[i].polygons_begin = 0;
		model->material_groups[i].polygons_count = 0;
		model->material_groups[i].smoothing = 0;
		model->material_groups[i].material = 0;
	}
	for(i = 0; i < model->vertices_count; i++)
	{
		model->vertices[i].x = 0.0f;
		model->vertices[i].y = 0.0f;
		model->vertices[i].z = 0.0f;
		model->vertices[i].w = 0.0f;
	}
	for(i = 0; i < model->polygons_count; i++)
	{
		model->polygons[i].normals_count = 0;
		model->polygons[i].texture_coordinates_count = 0;
		model->polygons[i].vertices_count = 0;
		model->polygons[i].normals = 0;
		model->polygons[i].vertices = 0;
		model->polygons[i].texture_coordinates = 0;
	}
	for(i = 0; i < model->texture_coordinates_count; i++)
	{
		model->texture_coordinates[i].u = 0.0f;
		model->texture_coordinates[i].v = 0.0f;
		model->texture_coordinates[i].w = 0.0f;
	}
	for(i = 0; i < model->normals_count; i++)
	{
		model->normals[i].i = 0;
		model->normals[i].j = 0;
		model->normals[i].k = 0;
	}

	for(i = 0; i < model->materials_count; i++)
	{
		model->materials[i].name = 0;
		model->materials[i].ambient.blue = 0;
		model->materials[i].ambient.green = 0;
		model->materials[i].ambient.red = 0;
		model->materials[i].diffuse.blue = 0;
		model->materials[i].diffuse.green = 0;
		model->materials[i].diffuse.red = 0;
		model->materials[i].dissolve_factor = 0;
		model->materials[i].emission.blue = 0;
		model->materials[i].emission.green = 0;
		model->materials[i].emission.red = 0;
		model->materials[i].illumination = 0;
		model->materials[i].index_of_refraction = 0;
		model->materials[i].specular.blue = 0;
		model->materials[i].specular.green = 0;
		model->materials[i].specular.red = 0;
		model->materials[i].specular_exponent = 0;

		model->materials[i].map_ambient.path = 0;
		model->materials[i].map_diffuse.path = 0;
		model->materials[i].map_dissolve.path = 0;
	}

	set_primary_attributes(model, model_file);
	set_derived_attributes(model, model_file);
}

void print_material(obj_material* material)
{
	printf("newmtl %s\n", material->name);
	printf("Ns %f\n", material->specular_exponent);
	printf("Ka %f %f %f\n", material->ambient.red, material->ambient.green, material->ambient.blue);
	printf("Kd %f %f %f\n", material->diffuse.red, material->diffuse.green, material->diffuse.blue);
	printf("Ks %f %f %f\n", material->specular.red, material->specular.green, material->specular.blue);
	printf("Ni %f\n", material->index_of_refraction);
	printf("d %f\n", material->dissolve_factor);
	printf("illum %lu\n", material->illumination);
	printf("map_Kd %s\n", material->map_diffuse.path);
	if(material->map_dissolve.path)
	{
		printf("map_d %s\n", material->map_dissolve.path);
	}
	printf("map_Ka %s\n", material->map_ambient.path);
}
obj_model* load_obj_file(const char* file_name)
{
	obj_model* model = new obj_model();

	//win slashes are evil!
	model->file_path = convert_slashes((obj_char*)file_name);

	FILE* model_file;

	model_file = fopen ((char*)model->file_path , "r");
	if (model_file == NULL)
	{
		perror("Error opening file");
	}
	else
	{
		count_and_allocate(model, model_file);

		fclose(model_file);
	}

	obj_unsigned_long_int i = 0;
	/*
	for(i = 0; i < model->objects_count; i++)
	{
		printf("\nobject no %lu\n", model->objects[i].groups_begin);
	}
	for(i = 0; i < model->materials_count; i++)
	{
		printf("material no %lu\n", i);
		print_material(&model->materials[i]);
	}*/

	/*obj_unsigned_long_int j = 0;
	obj_unsigned_long_int valid_material_groups = 0;
	for(i = 0; i < model->material_groups_count; i++)
	{
		if(model->material_groups[i].polygons_count > 0)
		{
			valid_material_groups++;
			printf("material group no %lu name: %s\n", i, model->material_groups[i].material->name);
			printf("\nmaterial group polygon count %lu\n", model->material_groups[i].polygons_count);
			printf("\nmaterial group smoothing: %u\n", model->material_groups[i].smoothing);
			for(j = model->material_groups[i].polygons_begin; j < model->material_groups[i].polygons_begin; j++)
			{

			}
		}
	}
	printf("\nvalid_material_groups: %lu\n", valid_material_groups);*/
	printf("done.\n");
	//exit(1);
	return model;
}
obj_model* create_test_obj()
{
	obj_model* test = new obj_model;

	test->file_path = new obj_char[100000];

	test->vertices_count = 10000;
	test->polygons_count = 10000;
	test->objects_count = 10000;
	test->texture_coordinates_count = 10000;
	test->normals_count = 10000;

	test->objects = new obj_object[test->objects_count];
	test->vertices = new obj_vertice[test->vertices_count];
	test->normals = new obj_normal[test->normals_count];
	test->texture_coordinates = new obj_texture_coordinate[test->texture_coordinates_count];
	test->polygons = new obj_polygon[test->polygons_count];

	obj_unsigned_long_int i = 0;

	for(i = 0; i < test->objects_count; i++)
	{
		test->objects[i].name = new obj_char[1000];
	}

	for(i = 0; i < test->polygons_count; i++)
	{
		test->polygons[i].vertices_count = 1;
		test->polygons[i].normals_count = 1;
		test->polygons[i].texture_coordinates_count = 1;

		for(obj_unsigned_long_int j = 0; j < test->polygons[i].vertices_count; j++)
		{
			test->polygons[i].vertices[j] = test->vertices[i];
			test->polygons[i].normals[j] = test->normals[i];
			test->polygons[i].texture_coordinates[j] = test->texture_coordinates[i];
		}

	}

	return test;
}

void delete_obj_model(obj_model* model)
{
	delete[] model->file_path;

	obj_unsigned_long_int i = 0;

	printf("\npreobjects delete\n");
	for(i = 0; i < model->objects_count; i++)
	{
		if(model->objects[i].name)
		{
			delete[] model->objects[i].name;
		}
	}
	delete[] model->objects;

	printf("\npost objects delete\n");

	delete[] model->vertices;

	printf("\npost vertices delete\n");


	delete[] model->normals;

	delete[] model->texture_coordinates;

	printf("\npre polygons delete\n");

	delete[] model->polygons;

	printf("\npre groups\n");
	for(i = 0; i < model->groups_count; i++)
	{
		if(model->groups[i].name)
		{
			delete[] model->groups[i].name;
		}
	}
	delete[] model->groups;
	printf("\npost groups\n");

	for(i = 0; i < model->materials_count; i++)
	{
		if(model->materials[i].name)
		{
			delete[] model->materials[i].name;
		}
		if(model->materials[i].map_ambient.path)
		{
			delete[] model->materials[i].map_ambient.path;
		}
		if(model->materials[i].map_diffuse.path)
		{
			delete[] model->materials[i].map_diffuse.path;
		}
	}
	delete[] model->materials;

	delete model;
	//printf("model->faces: %u\n",faces);
}

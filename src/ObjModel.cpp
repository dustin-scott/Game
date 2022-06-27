#include "ObjModel.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glu.h>

namespace game
{
	game_unsigned_int material_group_valid_count;
	GLuint* material_group_vertex_ids;
	game_unsigned_int* material_group_vertex_counts;
	GLuint* material_group_texture_coordinate_ids;
	game_unsigned_int* material_group_texture_coordinate_counts;
	GLuint* material_group_texture_ids;
	game_unsigned_int* material_group_normal_counts;
	GLuint* material_group_normal_ids;

	//game_unsigned_int* material_group_texture_counts;

	ObjModel::ObjModel(const char* model_path)
	{
		this->model = load_obj_file(model_path);
		this->compileVBO();
	}

	void ObjModel::compileVBO()
	{
		game_unsigned_int a = 0;
		game_unsigned_int b = 0;
		game_unsigned_int i = 0;
		game_unsigned_int j = 0;
		game_unsigned_int k = 0;

		game_unsigned_int material_group_iterator = 0;
		game_unsigned_int vert_iterator = 0;
		game_unsigned_int groups_begin = 0;
		game_unsigned_int groups_end = 0;
		game_unsigned_int texture_coordinate_iterator;
		game_unsigned_int normal_iterator;

		material_group_valid_count = 0;

		obj_unsigned_long_int actual =0 ;
		for(i = 0; i < this->model->objects_count; i++)
		{
			groups_begin = this->model->objects[i].groups_begin;
			groups_end = groups_begin+this->model->objects[i].groups_count;
			obj_group* group = 0;
			game_unsigned_int material_groups_begin = 0;
			game_unsigned_int material_groups_end = 0;
			for(j = groups_begin; j < groups_end; j++)
			{
				group = &this->model->groups[j];
				material_groups_begin = group->material_groups_begin;
				material_groups_end = material_groups_begin+group->material_groups_count;
				obj_material_group* material_group;
				material_group_iterator = 0;
				for(k = material_groups_begin; k < material_groups_end; k++)
				{
					material_group = &this->model->material_groups[k];

					game_unsigned_int polygons_begin = material_group->polygons_begin;
					game_unsigned_int polygons_end = polygons_begin+material_group->polygons_count;

					if(polygons_begin < polygons_end)
					{
						actual++;
					}
				}
			}
		}

		material_group_valid_count = actual;
		material_group_vertex_ids = new GLuint[material_group_valid_count];
		material_group_vertex_counts = new game_unsigned_int[material_group_valid_count];
		material_group_texture_coordinate_ids = new GLuint[material_group_valid_count];
		material_group_texture_coordinate_counts = new game_unsigned_int[material_group_valid_count];
		material_group_texture_ids = new GLuint[material_group_valid_count];
		material_group_normal_counts = new game_unsigned_int[material_group_valid_count];
		material_group_normal_ids = new GLuint[material_group_valid_count];

		glGenBuffersARB(material_group_valid_count, material_group_vertex_ids);
		glGenBuffersARB(material_group_valid_count, material_group_texture_coordinate_ids);
		glGenBuffersARB(material_group_valid_count, material_group_texture_ids);
		//glGenBuffersARB(material_group_valid_count, material_group_normal_ids);
		for(i = 0; i < material_group_valid_count; i++)
		{
			material_group_vertex_counts[i] = 0;
			material_group_texture_coordinate_counts[i] = 0;
			material_group_normal_counts[i] = 0;
		}

		for(a = 0; a < this->model->objects_count; a++)
		{
			if(this->model->objects[a].groups_count > 0)
			{
				for(b = this->model->objects[a].groups_begin; b < this->model->objects[a].groups_begin+this->model->objects[a].groups_count; b++)
				{
					if(this->model->groups[b].material_groups_count > 0)
					{
						for(i = this->model->groups[b].material_groups_begin; i < this->model->groups[b].material_groups_begin+this->model->groups[b].material_groups_count; i++)
						{
							if(this->model->material_groups[i].polygons_count > 0)
							{
								obj_material_group* material_group = &this->model->material_groups[i];

								for(j = material_group->polygons_begin; j <material_group->polygons_begin+material_group->polygons_count; j++)
								{
									material_group_vertex_counts[material_group_iterator] += this->model->polygons[j].vertices_count;
									material_group_texture_coordinate_counts[material_group_iterator] +=this->model->polygons[j].texture_coordinates_count;
									material_group_normal_counts[material_group_iterator] += this->model->polygons[j].normals_count;
								}

								vert_iterator = 0;
								texture_coordinate_iterator = 0;
								normal_iterator = 0;

								obj_vertice verts[material_group_vertex_counts[material_group_iterator]];
								for(j = 0; j < material_group_vertex_counts[material_group_iterator]; j++)
								{
									verts[j].x = 0.0f;
									verts[j].y = 0.0f;
									verts[j].z = 0.0f;
									verts[j].w = 0.0f;
								}

								obj_texture_coordinate texture_coordinate[material_group_texture_coordinate_counts[material_group_iterator]];
								for(j = 0; j < material_group_texture_coordinate_counts[material_group_iterator]; j++)
								{
									texture_coordinate[j].u = 0.0f;
									texture_coordinate[j].v = 0.0f;
									texture_coordinate[j].w = 0.0f;
								}

								//obj_normal normals[material_group_normal_counts[material_group_iterator]];
								for(j = material_group->polygons_begin; j < material_group->polygons_begin+material_group->polygons_count; j++)
								{
									obj_polygon* polygon = &this->model->polygons[j];
									for(k = 0; k < polygon->vertices_count; k++)
									{
										verts[vert_iterator].w = polygon->vertices[k].w;
										verts[vert_iterator].x = polygon->vertices[k].x;
										verts[vert_iterator].y = polygon->vertices[k].y;
										verts[vert_iterator].z = polygon->vertices[k].z;
										vert_iterator++;

										texture_coordinate[texture_coordinate_iterator].u = polygon->texture_coordinates[k].u;
										texture_coordinate[texture_coordinate_iterator].v = polygon->texture_coordinates[k].v;
										texture_coordinate[texture_coordinate_iterator].w = polygon->texture_coordinates[k].w;
										texture_coordinate_iterator++;

										//normals[normal_iterator].i = polygon->normals[k].i;
										//normals[normal_iterator].j = polygon->normals[k].j;
										//normals[normal_iterator].k = polygon->normals[k].k;
										normal_iterator++;
									}
								}
								glBindBufferARB(GL_ARRAY_BUFFER_ARB, material_group_vertex_ids[material_group_iterator]);
								glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(obj_vertice)*material_group_vertex_counts[material_group_iterator], &verts[0], GL_STATIC_DRAW_ARB);

								glBindBufferARB(GL_ARRAY_BUFFER_ARB, material_group_texture_coordinate_ids[material_group_iterator]);
								// upload data to VBO
								glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(obj_texture_coordinate)*material_group_texture_coordinate_counts[material_group_iterator], &texture_coordinate[0], GL_STATIC_DRAW_ARB);

								//glBindBufferARB(GL_ARRAY_BUFFER_ARB, material_group_normal_ids[material_group_iterator]);
								//glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(obj_normal)*material_group_normal_counts[material_group_iterator], &normals[0], GL_STATIC_DRAW_ARB);


								//material_group_texture_ids[material_group_iterator] = ilutGLLoadImage((char*)material_group->material->map_diffuse.path);
								glDisable(GL_TEXTURE_2D);
								//printf("object %s's map_ambient: %s\n", this->model->objects[i].name, material_group->material->map_ambient.path);
								material_group_iterator++;
							}
						}
					}
				}
			}
		}
	}
	void ObjModel::draw(void)
	{
		glMultMatrixf(this->coordinate_system.data);

		//glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		obj_unsigned_long_int i = 0;
		for(i = 0; i < material_group_valid_count; i++)
		{
			glEnable( GL_TEXTURE_2D );
			glBindTexture(GL_TEXTURE_2D, material_group_texture_ids[i]);
			//printf("\nvertex_count = %lu\n", material_group_vertex_counts[i]);
			// bind VBOs for vertex array and index array
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, material_group_texture_coordinate_ids[i]);
			glTexCoordPointer(3, GL_FLOAT, sizeof(obj_texture_coordinate), 0);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, material_group_vertex_ids[i]);         // for vertex coordinates
			glVertexPointer(4, GL_FLOAT, sizeof(obj_vertice), 0);               // last param is offset, not ptr

			//glBindBufferARB(GL_ARRAY_BUFFER_ARB, material_group_normal_ids[i]);         // for vertex coordinates
			//glNormalPointer(GL_FLOAT, sizeof(obj_normal), 0);

			// do same as vertex array except pointer
			glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			//glEnableClientState(GL_NORMAL_ARRAY);

			// draw 6 quads using offset of index array
			glColor3f(1.0f,1.0f,1.0f);
			glDrawArrays(GL_TRIANGLES, 0, material_group_vertex_counts[i]);

			glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			//glDisableClientState(GL_NORMAL_ARRAY);

			// bind with 0, so, switch back to normal pointer operation
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}
		glDisable(GL_BLEND);
		//glDisable(GL_LIGHTING);
	}
	ObjModel::~ObjModel()
	{
		glDeleteBuffersARB(material_group_valid_count, material_group_vertex_ids);
		glDeleteBuffersARB(material_group_valid_count, material_group_texture_coordinate_ids);
		glDeleteBuffersARB(material_group_valid_count, material_group_normal_ids);

		printf("\npreobj delete\n");
		delete_obj_model(this->model);
		printf("\npostobj delete\n");

		// delete VBO when program terminated
		delete[] material_group_vertex_ids;
		delete[] material_group_vertex_counts;
		delete[] material_group_texture_coordinate_ids;
		delete[] material_group_texture_coordinate_counts;
		delete[] material_group_texture_ids;
		delete[] material_group_normal_ids;
		delete[] material_group_normal_counts;

		//glDeleteBuffersARB(1, &textureId1);
	}

} /* namespace game */

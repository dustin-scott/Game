/*
 * ObjModel.h
 *
 *  Created on: Jan 12, 2013
 *      Author: Dustin Scott
 */

#ifndef OBJMODEL_H_
#define OBJMODEL_H_

#include "GameDrawable.h"
#include "obj_model.h"
namespace game
{
	class ObjModel: public game::GameDrawable
	{
		private:
			obj_model* model;
			void compileVBO();
		public:
			ObjModel(const char* model_path);
			virtual void draw(void);
			virtual ~ObjModel();
	};

} /* namespace game */
#endif /* OBJMODEL_H_ */

﻿#pragma once

#ifndef __CSC_GRAPHICS__
#error "∑(っ°Д° ;)っ : require 'csc_graphics.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("side_effects")
#pragma push_macro ("leftvalue")
#pragma push_macro ("rightvalue")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("switch_once")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef side_effects
#undef leftvalue
#undef rightvalue
#undef imports
#undef exports
#undef switch_once
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#pragma region
#pragma warning (push)
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (disable :5039)
#pragma warning (disable :26440)
#endif
#include <GL/glew.h>
#ifdef FREEGLUT_LIB_PRAGMAS
#error "∑(っ°Д° ;)っ : dont use 'FREEGLUT_LIB_PRAGMAS'"
#endif
#define FREEGLUT_LIB_PRAGMAS 0
#include <GL/freeglut.h>
#undef FREEGLUT_LIB_PRAGMAS
#pragma warning (pop)
#pragma endregion
#endif

#ifndef __GLEW_H__
#error "∑(っ°Д° ;)っ : require 'GL/glew.h'"
#endif

#ifndef __FREEGLUT_H__
#error "∑(っ°Д° ;)っ : require 'GL/freeglut.h'"
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
#ifndef use_comment_lib_glew32
#define use_comment_lib_glew32 "glew32.lib"
#endif
#pragma comment (lib ,use_comment_lib_glew32)
#undef use_comment_lib_glew32

#ifndef use_comment_lib_freeglut
#define use_comment_lib_freeglut "freeglut.lib"
#endif
#pragma comment (lib ,use_comment_lib_freeglut)
#undef use_comment_lib_freeglut

#ifndef use_comment_lib_glu32
#define use_comment_lib_glu32 "glu32.lib"
#endif
#pragma comment (lib ,use_comment_lib_glu32)
#undef use_comment_lib_glu32

#ifndef use_comment_lib_opengl32
#define use_comment_lib_opengl32 "opengl32.lib"
#endif

#pragma comment (lib ,use_comment_lib_opengl32)
#undef use_comment_lib_opengl32
#endif
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("side_effects")
#pragma pop_macro ("leftvalue")
#pragma pop_macro ("rightvalue")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("switch_once")
#pragma pop_macro ("discard")
#endif

namespace CSC {
namespace api {
using ::glCreateProgram ;
using ::glCreateShader ;
using ::glShaderSource ;
using ::glCompileShader ;
using ::glAttachShader ;
using ::glLinkProgram ;
using ::glDeleteProgram ;
using ::glUseProgram ;
using ::glGetUniformLocation ;
using ::glUniform1i ;
using ::glUniform1i64NV ;
using ::glUniform1f ;
using ::glUniform1d ;
using ::glUniform4fv ;
using ::glUniform4dv ;
using ::glUniformMatrix4fv ;
using ::glUniformMatrix4dv ;
using ::glGenVertexArrays ;
using ::glDeleteVertexArrays ;
using ::glGenBuffers ;
using ::glDeleteBuffers ;
using ::glGenTextures ;
using ::glDeleteTextures ;
using ::glBindVertexArray ;
using ::glActiveTexture ;
using ::glBindTexture ;
using ::glDrawArrays ;
using ::glGetShaderiv ;
using ::glGetShaderInfoLog ;
using ::glGetProgramiv ;
using ::glGetProgramInfoLog ;
using ::glBindBuffer ;
using ::glBufferData ;
using ::glEnableVertexAttribArray ;
using ::glVertexAttribPointer ;
using ::glTexParameteri ;
using ::glTexImage2D ;
using ::glGetError ;
} ;

class AbstractShader_Engine_OPENGL
	:public AbstractShader::Abstract {
private:
	//@warn: bind to (layout == 1) Vec3 in GLSL
	static constexpr auto LAYOUT_POSITION = CHAR (1) ;
	//@warn: bind to (layout == 2) Vec2 in GLSL
	static constexpr auto LAYOUT_TEXCOORD = CHAR (2) ;
	//@warn: bind to (layout == 3) Vec3 in GLSL
	static constexpr auto LAYOUT_NORMAL = CHAR (3) ;

	struct SELF_PACK {
		UniqueRef<CHAR> mVAO ;
		UniqueRef<AutoBuffer<CHAR>> mVBO ;
		UniqueRef<AutoBuffer<CHAR>> mVTO ;
		LENGTH mSize ;
		FLAG mMode ;
		INDEX mTexture ;
	} ;

	using NATIVE_THIS = UniqueRef<CHAR> ;
	using SPRITE_NATIVE_THIS = SELF_PACK ;

public:
 	implicit AbstractShader_Engine_OPENGL () {
		_STATIC_ASSERT_ (_SIZEOF_ (DEF<decltype (DEREF[this])>) == _SIZEOF_ (Interface)) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (DEF<decltype (DEREF[this])>) == _ALIGNOF_ (Interface)) ;
	}

	void compute_load_data (AnyRef<> &holder ,const PhanBuffer<const BYTE> &vs ,const PhanBuffer<const BYTE> &fs) const override {
		_DEBUG_ASSERT_ (vs.size () < VAR32_MAX) ;
		_DEBUG_ASSERT_ (fs.size () < VAR32_MAX) ;
		auto tmp = UniqueRef<CHAR> ([&] (CHAR &me) {
			me = api::glCreateProgram () ;
			_DYNAMIC_ASSERT_ (me != 0) ;
			const auto r1x = api::glCreateShader (GL_VERTEX_SHADER) ;
			const auto r2x = _POINTER_CAST_ (ARGV<ARR<STRA>>::null ,DEPTR[vs.self]) ;
			const auto r3x = DEPTR[DEREF[r2x][0]] ;
			const auto r4x = VAR32 (vs.size ()) ;
			api::glShaderSource (r1x ,1 ,DEPTR[r3x] ,DEPTR[r4x]) ;
			api::glCompileShader (r1x) ;
			compute_check_shaderiv (r1x) ;
			api::glAttachShader (me ,r1x) ;
			const auto r5x = api::glCreateShader (GL_FRAGMENT_SHADER) ;
			const auto r6x = _POINTER_CAST_ (ARGV<ARR<STRA>>::null ,DEPTR[fs.self]) ;
			const auto r7x = DEPTR[DEREF[r6x][0]] ;
			const auto r8x = VAR32 (fs.size ()) ;
			api::glShaderSource (r5x ,1 ,DEPTR[r7x] ,DEPTR[r8x]) ;
			api::glCompileShader (r5x) ;
			compute_check_shaderiv (r5x) ;
			api::glAttachShader (me ,r5x) ;
			api::glLinkProgram (me) ;
			compute_check_programiv (me) ;
		} ,[] (CHAR &me) {
			api::glDeleteProgram (me) ;
		}) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_active_pipeline (AnyRef<> &holder) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		api::glUseProgram (r1x) ;
	}

	void compute_uniform_find (AnyRef<> &holder ,const String<STR> &name ,INDEX &index) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = identity_name (name) ;
		index = INDEX (api::glGetUniformLocation (r1x ,r2x.raw ().self)) ;
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const VAR32 &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		api::glUniform1i (VAR32 (index) ,data) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const VAR64 &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		api::glUniform1i64NV (VAR32 (index) ,data) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const VAL32 &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		api::glUniform1f (VAR32 (index) ,data) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const VAL64 &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		api::glUniform1d (VAR32 (index) ,data) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const Vector<VAL32> &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		const auto r1x = ARRAY4<VAL32> {data[0] ,data[1] ,data[2] ,data[3]} ;
		api::glUniform4fv (VAR32 (index) ,1 ,r1x.raw ().self) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const Vector<VAL64> &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		const auto r1x = ARRAY4<VAL64> {data[0] ,data[1] ,data[2] ,data[3]} ;
		api::glUniform4dv (VAR32 (index) ,1 ,r1x.raw ().self) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const Matrix<VAL32> &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		const auto r1x = Array<VAL32 ,ARGC<16>> ({
			data[0][0] ,data[0][1] ,data[0][2] ,data[0][3] ,
			data[1][0] ,data[1][1] ,data[1][2] ,data[1][3] ,
			data[2][0] ,data[2][1] ,data[2][2] ,data[2][3] ,
			data[3][0] ,data[3][1] ,data[3][2] ,data[3][3]}) ;
		api::glUniformMatrix4fv (VAR32 (index) ,1 ,GL_TRUE ,r1x.raw ().self) ;
	}

	void compute_uniform_write (AnyRef<> &holder ,const INDEX &index ,const Matrix<VAL64> &data) const override {
		_DEBUG_ASSERT_ (index != GL_INVALID_VALUE) ;
		const auto r1x = Array<VAL64 ,ARGC<16>> ({
			data[0][0] ,data[0][1] ,data[0][2] ,data[0][3] ,
			data[1][0] ,data[1][1] ,data[1][2] ,data[1][3] ,
			data[2][0] ,data[2][1] ,data[2][2] ,data[2][3] ,
			data[3][0] ,data[3][1] ,data[3][2] ,data[3][3]}) ;
		api::glUniformMatrix4dv (VAR32 (index) ,1 ,GL_TRUE ,r1x.raw ().self) ;
	}

	void compute_sprite_load_data (AnyRef<> &holder ,const Mesh &mesh) const override {
		auto tmp = SELF_PACK () ;
		tmp.mVAO = UniqueRef<CHAR> ([&] (CHAR &me) {
			api::glGenVertexArrays (1 ,DEPTR[me]) ;
			_DYNAMIC_ASSERT_ (me != GL_INVALID_VALUE) ;
		} ,[] (CHAR &me) {
			api::glDeleteVertexArrays (1 ,DEPTR[me]) ;
		}) ;
		tmp.mVBO = UniqueRef<AutoBuffer<CHAR>> ([&] (AutoBuffer<CHAR> &me) {
			me = AutoBuffer<CHAR> (1) ;
			api::glGenBuffers (VAR32 (me.size ()) ,me.self) ;
		} ,[] (AutoBuffer<CHAR> &me) {
			api::glDeleteBuffers (VAR32 (me.size ()) ,me.self) ;
		}) ;
		tmp.mVTO = UniqueRef<AutoBuffer<CHAR>> ([&] (AutoBuffer<CHAR> &me) {
			me = AutoBuffer<CHAR> (1) ;
			api::glGenTextures (VAR32 (me.size ()) ,me.self) ;
		} ,[] (AutoBuffer<CHAR> &me) {
			api::glDeleteTextures (VAR32 (me.size ()) ,me.self) ;
		}) ;
		const auto r1x = bind_vertex (mesh.vertex () ,mesh.element ()) ;
		compute_transfer_data (tmp ,r1x) ;
		compute_transfer_data (tmp ,mesh.texture ()[0]) ;
		holder = AnyRef<SPRITE_NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_sprite_active_texture (AnyRef<> &holder ,const INDEX &texture) const override {
		auto &r1x = holder.rebind (ARGV<SPRITE_NATIVE_THIS>::null).self ;
		_DYNAMIC_ASSERT_ (texture >= 0 && texture < r1x.mVTO->size ()) ;
		r1x.mTexture = texture ;
	}

	void compute_sprite_draw (AnyRef<> &holder) const override {
		auto &r1x = holder.rebind (ARGV<SPRITE_NATIVE_THIS>::null).self ;
		api::glBindVertexArray (r1x.mVAO) ;
		if switch_once (TRUE) {
			if (r1x.mTexture == VAR_NONE)
				discard ;
			api::glActiveTexture (GL_TEXTURE_2D) ;
			api::glBindTexture (GL_TEXTURE_2D ,r1x.mVTO.self[r1x.mTexture]) ;
		}
		api::glDrawArrays (CHAR (r1x.mMode) ,0 ,VAR32 (r1x.mSize)) ;
	}

private:
	void compute_check_shaderiv (const CHAR &shader) const {
		auto rax = ARRAY2<VAR32> () ;
		rax[0] = GL_FALSE ;
		api::glGetShaderiv (shader ,GL_COMPILE_STATUS ,DEPTR[rax[0]]) ;
		if (rax[0] == GL_TRUE)
			return ;
		rax[1] = 0 ;
		api::glGetShaderiv (shader ,GL_INFO_LOG_LENGTH ,DEPTR[rax[1]]) ;
		if (rax[1] <= 0)
			return ;
		auto rbx = String<STRA> (rax[1]) ;
		api::glGetShaderInfoLog (shader ,VAR32 (rbx.size ()) ,NULL ,rbx.raw ().self) ;
		_DYNAMIC_ASSERT_ (rbx.empty ()) ;
	}

	void compute_check_programiv (const CHAR &shader) const {
		auto rax = ARRAY2<VAR32> () ;
		rax[0] = GL_FALSE ;
		api::glGetProgramiv (shader ,GL_LINK_STATUS ,DEPTR[rax[0]]) ;
		if (rax[0] == GL_TRUE)
			return ;
		rax[1] = 0 ;
		api::glGetProgramiv (shader ,GL_INFO_LOG_LENGTH ,DEPTR[rax[1]]) ;
		if (rax[1] <= 0)
			return ;
		auto rbx = String<STRA> (rax[1]) ;
		api::glGetProgramInfoLog (shader ,VAR32 (rbx.size ()) ,NULL ,rbx.raw ().self) ;
		_DYNAMIC_ASSERT_ (rbx.empty ()) ;
	}

	Array<ARRAY1<ARRAY3<VAL32>>> bind_vertex (const Set<ARRAY3<VAL32>> &vertex ,const Deque<ARRAY1<INDEX>> &element) const {
		Array<ARRAY1<ARRAY3<VAL32>>> ret = Array<ARRAY1<ARRAY3<VAL32>>> (element.length ()) ;
		for (auto &&i : _RANGE_ (0 ,element.length ())) {
			INDEX ix = element.access (i) ;
			ret[i][0] = vertex[element[ix][0]] ;
		}
		return _MOVE_ (ret) ;
	}

	Array<ARRAY2<ARRAY3<VAL32>>> bind_vertex (const Set<ARRAY3<VAL32>> &vertex ,const Deque<ARRAY2<INDEX>> &element) const {
		Array<ARRAY2<ARRAY3<VAL32>>> ret = Array<ARRAY2<ARRAY3<VAL32>>> (element.length ()) ;
		for (auto &&i : _RANGE_ (0 ,element.length ())) {
			INDEX ix = element.access (i) ;
			ret[i][0] = vertex[element[ix][0]] ;
			ret[i][1] = vertex[element[ix][1]] ;
		}
		return _MOVE_ (ret) ;
	}

	Array<ARRAY3<ARRAY3<VAL32>>> bind_vertex (const Set<ARRAY3<VAL32>> &vertex ,const Deque<ARRAY3<INDEX>> &element) const {
		Array<ARRAY3<ARRAY3<VAL32>>> ret = Array<ARRAY3<ARRAY3<VAL32>>> (element.length ()) ;
		for (auto &&i : _RANGE_ (0 ,element.length ())) {
			INDEX ix = element.access (i) ;
			ret[i][0] = vertex[element[ix][0]] ;
			ret[i][1] = vertex[element[ix][1]] ;
			ret[i][2] = vertex[element[ix][2]] ;
		}
		return _MOVE_ (ret) ;
	}

	Array<ARRAY4<ARRAY3<VAL32>>> bind_vertex (const Set<ARRAY3<VAL32>> &vertex ,const Deque<ARRAY4<INDEX>> &element) const {
		Array<ARRAY4<ARRAY3<VAL32>>> ret = Array<ARRAY4<ARRAY3<VAL32>>> (element.length ()) ;
		for (auto &&i : _RANGE_ (0 ,element.length ())) {
			INDEX ix = element.access (i) ;
			ret[i][0] = vertex[element[ix][0]] ;
			ret[i][1] = vertex[element[ix][1]] ;
			ret[i][2] = vertex[element[ix][2]] ;
			ret[i][3] = vertex[element[ix][3]] ;
		}
		return _MOVE_ (ret) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY1<ARRAY3<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY3<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_POINTS ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,NULL) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY2<ARRAY3<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY3<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_LINES ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,NULL) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY2<ARRAY5<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY5<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_LINES ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		const auto r2x = DEPTR[_NULL_ (ARGV<ARRAY5<VAL32>>::null)[0]] ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r2x) ;
		api::glEnableVertexAttribArray (LAYOUT_TEXCOORD) ;
		const auto r3x = DEPTR[_NULL_ (ARGV<ARRAY5<VAL32>>::null)[3]] ;
		api::glVertexAttribPointer (LAYOUT_TEXCOORD ,2 ,GL_FLOAT ,GL_FALSE ,r1x ,r3x) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY3<ARRAY3<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY3<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_TRIANGLES ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,NULL) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY3<ARRAY5<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY5<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_TRIANGLES ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		const auto r2x = DEPTR[_NULL_ (ARGV<ARRAY5<VAL32>>::null)[0]] ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r2x) ;
		api::glEnableVertexAttribArray (LAYOUT_TEXCOORD) ;
		const auto r3x = DEPTR[_NULL_ (ARGV<ARRAY5<VAL32>>::null)[3]] ;
		api::glVertexAttribPointer (LAYOUT_TEXCOORD ,2 ,GL_FLOAT ,GL_FALSE ,r1x ,r3x) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY3<ARRAY8<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY8<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_TRIANGLES ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		const auto r2x = DEPTR[_NULL_ (ARGV<ARRAY8<VAL32>>::null)[0]] ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r2x) ;
		api::glEnableVertexAttribArray (LAYOUT_TEXCOORD) ;
		const auto r3x = DEPTR[_NULL_ (ARGV<ARRAY8<VAL32>>::null)[3]] ;
		api::glVertexAttribPointer (LAYOUT_TEXCOORD ,2 ,GL_FLOAT ,GL_FALSE ,r1x ,r3x) ;
		api::glEnableVertexAttribArray (LAYOUT_NORMAL) ;
		const auto r4x = DEPTR[_NULL_ (ARGV<ARRAY8<VAL32>>::null)[5]] ;
		api::glVertexAttribPointer (LAYOUT_NORMAL ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r4x) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY4<ARRAY3<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY3<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_QUADS ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,NULL) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY4<ARRAY5<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY5<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_QUADS ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		const auto r2x = DEPTR[_NULL_ (ARGV<ARRAY5<VAL32>>::null)[0]] ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r2x) ;
		api::glEnableVertexAttribArray (LAYOUT_TEXCOORD) ;
		const auto r3x = DEPTR[_NULL_ (ARGV<ARRAY5<VAL32>>::null)[3]] ;
		api::glVertexAttribPointer (LAYOUT_TEXCOORD ,2 ,GL_FLOAT ,GL_FALSE ,r1x ,r3x) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Array<ARRAY4<ARRAY8<VAL32>>> &vbo) const {
		const auto r1x = _SIZEOF_ (ARRAY8<VAL32>) ;
		self_.mSize = vbo.length () * vbo[0].length () ;
		self_.mMode = GL_QUADS ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindBuffer (GL_ARRAY_BUFFER ,self_.mVBO.self[0]) ;
		api::glBufferData (GL_ARRAY_BUFFER ,(self_.mSize * r1x) ,vbo[0][0].raw ().self ,GL_STATIC_DRAW) ;
		api::glEnableVertexAttribArray (LAYOUT_POSITION) ;
		const auto r2x = DEPTR[_NULL_ (ARGV<ARRAY8<VAL32>>::null)[0]] ;
		api::glVertexAttribPointer (LAYOUT_POSITION ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r2x) ;
		api::glEnableVertexAttribArray (LAYOUT_TEXCOORD) ;
		const auto r3x = DEPTR[_NULL_ (ARGV<ARRAY8<VAL32>>::null)[3]] ;
		api::glVertexAttribPointer (LAYOUT_TEXCOORD ,2 ,GL_FLOAT ,GL_FALSE ,r1x ,r3x) ;
		api::glEnableVertexAttribArray (LAYOUT_NORMAL) ;
		const auto r4x = DEPTR[_NULL_ (ARGV<ARRAY8<VAL32>>::null)[5]] ;
		api::glVertexAttribPointer (LAYOUT_NORMAL ,3 ,GL_FLOAT ,GL_FALSE ,r1x ,r4x) ;
		api::glBindVertexArray (0) ;
	}

	void compute_transfer_data (SELF_PACK &self_ ,const Bitmap<COLOR_BGR> &image) const {
		self_.mTexture = 0 ;
		api::glBindVertexArray (self_.mVAO) ;
		api::glBindTexture (GL_TEXTURE_2D ,self_.mVTO.self[0]) ;
		api::glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_WRAP_S ,GL_REPEAT) ;
		api::glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_WRAP_T ,GL_REPEAT) ;
		api::glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_MAG_FILTER ,GL_LINEAR) ;
		api::glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_MIN_FILTER ,GL_LINEAR) ;
		api::glTexImage2D (GL_TEXTURE_2D ,0 ,GL_RGB ,VAR32 (image.cx ()) ,VAR32 (image.cy ()) ,0 ,GL_BGR ,GL_UNSIGNED_BYTE ,image.raw ().self) ;
		api::glBindVertexArray (0) ;
	}

	String<STRA> identity_name (const String<STR> &name) const {
		String<STRA> ret = String<STRA> (name.length ()) ;
		for (auto &&i : _RANGE_ (0 ,ret.size ())) {
			const auto r1x = BOOL (name[i] >= STR ('a') && name[i] <= STR ('z')) ;
			const auto r2x = BOOL (name[i] >= STR ('A') && name[i] <= STR ('Z')) ;
			const auto r3x = BOOL (name[i] >= STR ('0') && name[i] <= STR ('9')) ;
			const auto r4x = BOOL (name[i] == STR ('_')) ;
			_DEBUG_ASSERT_ (r1x || r2x || r3x || r4x) ;
			ret[i] = STRA (name[i]) ;
		}
		return _MOVE_ (ret) ;
	}

	void compute_check_error (UniqueRef<CHAR> &self_) const {
		const auto r1x = api::glGetError () ;
		_DYNAMIC_ASSERT_ (r1x == GL_NO_ERROR) ;
	}
} ;
} ;
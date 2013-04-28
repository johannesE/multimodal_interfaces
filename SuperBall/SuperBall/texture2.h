/*
 * Texture image definitions from Chapter 8.
 *
 * Written by Michael Sweet
 */

/*
* Révisions :
* 06. 01. 2006 : PCH
* Changer le nom du fichier :
* Texture.h  --> Texture2.h
*/

/*
 * Include necessary headers.
 */

#ifndef _TEXTURE2_H_
#  define _TEXTURE2_H_

#  include "bitmap2.h"


/*
 * Make this header file work with C and C++ source code...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

extern GLuint TextureLoad(char *filename, GLboolean alpha,
                          GLenum minfilter, GLenum magfilter,
			  GLenum wrap);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_TEXTURE2_H_ */

/*
 * End of "$Id: texture.h,v 1.1 1999/09/27 02:50:03 mike Exp $".
 */

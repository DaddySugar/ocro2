# ifndef BITMAP_H_DEFINED
# define BITMAP_H_DEFINED
# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>


# pragma pack(push, 1)
struct s_color
{
  unsigned char b; /*!< Th blue color */
  unsigned char g; /*!< The green color */
  unsigned char r; /*!< The red color */
};
# pragma pack(pop)
typedef struct s_color color;


color newColor(unsigned char, unsigned char, unsigned char);

# pragma pack(push, 1)
struct s_bitmap
{
  unsigned width; /*!< The width of the picture */
  unsigned height; /*!< The height of the picture */
  color *content; /*!< The table of color */
};
# pragma pack(pop)

typedef struct s_bitmap bitmap;


bitmap *newBitmap(unsigned, unsigned, color *);
void freeBitmap(bitmap *);
void draw(bitmap *);
void binarize(bitmap *);
void resize(bitmap *);
bitmap *loadBmp(SDL_Surface *downloadBMP);
void autoContrast(bitmap *);
# endif

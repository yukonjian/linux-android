1. freetype库实现文字显示
https://blog.csdn.net/guoke312/article/details/79562920

bitmap_left = FTFace->glyph->bitmap_left; // 字符距离左边界的距离
bitmap_top = FTFace->glyph->bitmap_top; // 字符最高点距离基线的距离
Ascender = FTFace->size->metrics.ascender >> 6; // 基线到字符轮廓最高点的距离, 由于是26.6的定点数，因此获取整数部分需要除以64
charposx = posx + bitmap_left;
charposy = posy - Ascender + bitmap_top;

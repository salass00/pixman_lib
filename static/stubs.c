/*
 * AmigaOS shared library implementation of libpixman-1.
 *
 * Copyright 2017 Fredrik Wikstrom <fredrik@a500.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <interfaces/pixman.h>

asm("\t.section\t\".text\"\n"
	"\t.align\t2\n"
	"\t.globl\t__CallPixman\n"
	"\t.type\t__CallPixman, @function\n"
	"__CallPixman:\n"
	"\tlis\t%r11,IPixman@ha\n"
	"\tlwz\t%r0,IPixman@l(%r11)\n"
	"\tlwzx\t%r11,%r12,%r0\n"
	"\tmtctr\t%r11\n"
	"\tbctr\n"
	"\t.size\t__CallPixman, .-__CallPixman");

#define PixmanCall(function, offset) \
asm("\t.section\t\".text\"\n" \
	"\t.align\t2\n" \
	"\t.globl\t" #function "\n" \
	"\t.type\t" #function ", @function\n" \
	#function ":\n" \
	"\tli\t%r12," #offset "\n" \
	"\tb\t__CallPixman\n" \
	"\t.size\t" #function ", .-" #function);

PixmanCall(pixman_transform_init_identity, 76)
PixmanCall(pixman_transform_point_3d, 80)
PixmanCall(pixman_transform_point, 84)
PixmanCall(pixman_transform_multiply, 88)
PixmanCall(pixman_transform_init_scale, 92)
PixmanCall(pixman_transform_scale, 96)
PixmanCall(pixman_transform_init_rotate, 100)
PixmanCall(pixman_transform_rotate, 104)
PixmanCall(pixman_transform_init_translate, 108)
PixmanCall(pixman_transform_translate, 112)
PixmanCall(pixman_transform_bounds, 116)
PixmanCall(pixman_transform_invert, 120)
PixmanCall(pixman_transform_is_identity, 124)
PixmanCall(pixman_transform_is_scale, 128)
PixmanCall(pixman_transform_is_int_translate, 132)
PixmanCall(pixman_transform_is_inverse, 136)
PixmanCall(pixman_transform_from_pixman_f_transform, 140)
PixmanCall(pixman_f_transform_from_pixman_transform, 144)
PixmanCall(pixman_f_transform_invert, 148)
PixmanCall(pixman_f_transform_point, 152)
PixmanCall(pixman_f_transform_point_3d, 156)
PixmanCall(pixman_f_transform_multiply, 160)
PixmanCall(pixman_f_transform_init_scale, 164)
PixmanCall(pixman_f_transform_scale, 168)
PixmanCall(pixman_f_transform_init_rotate, 172)
PixmanCall(pixman_f_transform_rotate, 176)
PixmanCall(pixman_f_transform_init_translate, 180)
PixmanCall(pixman_f_transform_translate, 184)
PixmanCall(pixman_f_transform_bounds, 188)
PixmanCall(pixman_f_transform_init_identity, 192)
PixmanCall(pixman_region_set_static_pointers, 196)
PixmanCall(pixman_region_init, 200)
PixmanCall(pixman_region_init_rect, 204)
PixmanCall(pixman_region_init_rects, 208)
PixmanCall(pixman_region_init_with_extents, 212)
PixmanCall(pixman_region_init_from_image, 216)
PixmanCall(pixman_region_fini, 220)
PixmanCall(pixman_region_translate, 224)
PixmanCall(pixman_region_copy, 228)
PixmanCall(pixman_region_intersect, 232)
PixmanCall(pixman_region_union, 236)
PixmanCall(pixman_region_union_rect, 240)
PixmanCall(pixman_region_intersect_rect, 244)
PixmanCall(pixman_region_subtract, 248)
PixmanCall(pixman_region_inverse, 252)
PixmanCall(pixman_region_contains_point, 256)
PixmanCall(pixman_region_contains_rectangle, 260)
PixmanCall(pixman_region_not_empty, 264)
PixmanCall(pixman_region_extents, 268)
PixmanCall(pixman_region_n_rects, 272)
PixmanCall(pixman_region_rectangles, 276)
PixmanCall(pixman_region_equal, 280)
PixmanCall(pixman_region_selfcheck, 284)
PixmanCall(pixman_region_reset, 288)
PixmanCall(pixman_region_clear, 292)
PixmanCall(pixman_region32_init, 296)
PixmanCall(pixman_region32_init_rect, 300)
PixmanCall(pixman_region32_init_rects, 304)
PixmanCall(pixman_region32_init_with_extents, 308)
PixmanCall(pixman_region32_init_from_image, 312)
PixmanCall(pixman_region32_fini, 316)
PixmanCall(pixman_region32_translate, 320)
PixmanCall(pixman_region32_copy, 324)
PixmanCall(pixman_region32_intersect, 328)
PixmanCall(pixman_region32_union, 332)
PixmanCall(pixman_region32_intersect_rect, 336)
PixmanCall(pixman_region32_union_rect, 340)
PixmanCall(pixman_region32_subtract, 344)
PixmanCall(pixman_region32_inverse, 348)
PixmanCall(pixman_region32_contains_point, 352)
PixmanCall(pixman_region32_contains_rectangle, 356)
PixmanCall(pixman_region32_not_empty, 360)
PixmanCall(pixman_region32_extents, 364)
PixmanCall(pixman_region32_n_rects, 368)
PixmanCall(pixman_region32_rectangles, 372)
PixmanCall(pixman_region32_equal, 376)
PixmanCall(pixman_region32_selfcheck, 380)
PixmanCall(pixman_region32_reset, 384)
PixmanCall(pixman_region32_clear, 388)
PixmanCall(pixman_blt, 392)
PixmanCall(pixman_fill, 396)
PixmanCall(pixman_version, 400)
PixmanCall(pixman_version_string, 404)
PixmanCall(pixman_format_supported_destination, 408)
PixmanCall(pixman_format_supported_source, 412)
PixmanCall(pixman_image_create_solid_fill, 416)
PixmanCall(pixman_image_create_linear_gradient, 420)
PixmanCall(pixman_image_create_radial_gradient, 424)
PixmanCall(pixman_image_create_conical_gradient, 428)
PixmanCall(pixman_image_create_bits, 432)
PixmanCall(pixman_image_create_bits_no_clear, 436)
PixmanCall(pixman_image_ref, 440)
PixmanCall(pixman_image_unref, 444)
PixmanCall(pixman_image_set_destroy_function, 448)
PixmanCall(pixman_image_get_destroy_data, 452)
PixmanCall(pixman_image_set_clip_region, 456)
PixmanCall(pixman_image_set_clip_region32, 460)
PixmanCall(pixman_image_set_has_client_clip, 464)
PixmanCall(pixman_image_set_transform, 468)
PixmanCall(pixman_image_set_repeat, 472)
PixmanCall(pixman_image_set_filter, 476)
PixmanCall(pixman_image_set_source_clipping, 480)
PixmanCall(pixman_image_set_alpha_map, 484)
PixmanCall(pixman_image_set_component_alpha, 488)
PixmanCall(pixman_image_get_component_alpha, 492)
PixmanCall(pixman_image_set_accessors, 496)
PixmanCall(pixman_image_set_indexed, 500)
PixmanCall(pixman_image_get_data, 504)
PixmanCall(pixman_image_get_width, 508)
PixmanCall(pixman_image_get_height, 512)
PixmanCall(pixman_image_get_stride, 516)
PixmanCall(pixman_image_get_depth, 520)
PixmanCall(pixman_image_get_format, 524)
PixmanCall(pixman_filter_create_separable_convolution, 528)
PixmanCall(pixman_image_fill_rectangles, 532)
PixmanCall(pixman_image_fill_boxes, 536)
PixmanCall(pixman_compute_composite_region, 540)
PixmanCall(pixman_image_composite, 544)
PixmanCall(pixman_image_composite32, 548)
PixmanCall(pixman_disable_out_of_bounds_workaround, 552)
PixmanCall(pixman_glyph_cache_create, 556)
PixmanCall(pixman_glyph_cache_destroy, 560)
PixmanCall(pixman_glyph_cache_freeze, 564)
PixmanCall(pixman_glyph_cache_thaw, 568)
PixmanCall(pixman_glyph_cache_lookup, 572)
PixmanCall(pixman_glyph_cache_insert, 576)
PixmanCall(pixman_glyph_cache_remove, 580)
PixmanCall(pixman_glyph_get_extents, 584)
PixmanCall(pixman_glyph_get_mask_format, 588)
PixmanCall(pixman_composite_glyphs, 592)
PixmanCall(pixman_composite_glyphs_no_mask, 596)
PixmanCall(pixman_sample_ceil_y, 600)
PixmanCall(pixman_sample_floor_y, 604)
PixmanCall(pixman_edge_step, 608)
PixmanCall(pixman_edge_init, 612)
PixmanCall(pixman_line_fixed_edge_init, 616)
PixmanCall(pixman_rasterize_edges, 620)
PixmanCall(pixman_add_traps, 624)
PixmanCall(pixman_add_trapezoids, 628)
PixmanCall(pixman_rasterize_trapezoid, 632)
PixmanCall(pixman_composite_trapezoids, 636)
PixmanCall(pixman_composite_triangles, 640)
PixmanCall(pixman_add_triangles, 644)


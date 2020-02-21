#pragma once

void array_fold(const void* src, const size_t size, const size_t count, void* start, void* result, void folder(const void*, const void*, void*));
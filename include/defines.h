#pragma once

#define M_PI		3.14159265358979323846

#define abs(a) ((a) < 0 ? -(a) : (a))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
#define swap(a,b) do { a+=b; b=a-b; a-=b; } while(0)
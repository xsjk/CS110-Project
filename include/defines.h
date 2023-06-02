#pragma once

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
#define swap(a,b) do { a+=b; b=a-b; a-=b; } while(0)
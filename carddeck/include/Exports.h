#pragma once

#ifdef CARDDECK_EXPORTS
#define CARDDECK_API __declspec(dllexport) 
#else
#define CARDDECK_API __declspec(dllimport) 
#endif
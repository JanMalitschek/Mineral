/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Bahnschrift_ttf;
    const int            Bahnschrift_ttfSize = 355600;

    extern const char*   Bebas_ttf;
    const int            Bebas_ttfSize = 64432;

    extern const char*   MIDI_Note_Icon_svg;
    const int            MIDI_Note_Icon_svgSize = 2200;

    extern const char*   MIDI_Velocity_Icon_svg;
    const int            MIDI_Velocity_Icon_svgSize = 2492;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 4;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}

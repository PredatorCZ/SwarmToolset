/*  LibSwarm
    Copyright(C) 2023-2026 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include "spike/util/detail/sc_architecture.hpp"

#ifdef SW_EXPORT
#define SW_EXTERN ES_EXPORT
#elif defined(SW_IMPORT)
#define SW_EXTERN ES_IMPORT
#else
#define SW_EXTERN
#endif

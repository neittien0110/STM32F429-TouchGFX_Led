/******************************************************************************
<<<<<<< HEAD
* Copyright (c) 2018(-2026) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.26.1 distribution.
=======
* Copyright (c) 2018(-2025) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.25.0 distribution.
>>>>>>> 36eda1fcc4fe8a02a78bda2603ca51ed36603514
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

#include <touchgfx/widgets/TouchArea.hpp>

namespace touchgfx
{
class ClickEvent;

void TouchArea::handleClickEvent(const ClickEvent& event)
{
    AbstractButton::handleClickEvent(event);
    if (pressedAction && pressedAction->isValid() && pressed)
    {
        pressedAction->execute(*this);
    }
}
} // namespace touchgfx

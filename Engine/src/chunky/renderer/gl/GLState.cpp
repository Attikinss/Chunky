#include "GLState.h"

#include <glad/gl.h>

namespace Chunky
{
    void GLState::SetEnabled(bool enabled)
    {
        if (enabled == m_Enabled)
            return;

        m_Enabled = enabled;
        if (enabled)
            glEnable(m_State);
        else
            glDisable(m_State);
    }
}
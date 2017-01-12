#include "stdafx.h"
#include "GameObject.h"

void GameObject::wrapPositions(Camera & cam)
{
	cam.Wrap(m_bounds);
}

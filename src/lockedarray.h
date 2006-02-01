/*
 *  The Mana World
 *  Copyright 2004 The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  The Mana World is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  The Mana World is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Mana World; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  $Id$
 */

#ifndef _TMW_LOCKEDARRAY_H
#define _TMW_LOCKEDARRAY_H

/**
 * A _very_ basic array class that allows simple iteration and jumps, keeping
 * its currently selected entry and providing a mechanism to lock this
 * position. Anyone can unlock it though, so its your job to use it the right
 * way ;)
 */

template<class T>
class LockedArray
{
    public:
        LockedArray(unsigned int size);
        ~LockedArray();

        void lock() { mLocked = true; };
        void unlock() { mLocked = false; };

        bool isLocked() const { return mLocked; };

        T getEntry() const { return mData[mCurEntry]; };
        void setEntry(T entry) { mData[mCurEntry] = entry; };

        void next();
        void prev();
        void select(unsigned int pos);
        unsigned int getPos() const { return mCurEntry; }

        unsigned int getSize() const { return mSize; };

    protected:
        unsigned int mSize;

        T* mData;

        unsigned int mCurEntry;
        bool mLocked;
};

template<class T>
LockedArray<T>::LockedArray(unsigned int size):
    mSize(size), mData(new T[size]), mCurEntry(0), mLocked(false)
{
    for (unsigned int i = 0; i < mSize; i++)
        mData[i] = 0;
}

template<class T>
LockedArray<T>::~LockedArray()
{
    if (mData)
        delete [] mData;
}

template<class T>
void LockedArray<T>::next()
{
    if (mLocked)
        return;

    if (++mCurEntry == mSize)
        mCurEntry = 0;
}

template<class T>
void LockedArray<T>::prev()
{
    if (mLocked)
        return;

    mCurEntry = mCurEntry ? (--mCurEntry) : (mSize - 1);
}

template<class T>
void LockedArray<T>::select(unsigned int pos)
{
    if (mLocked)
        return;

    mCurEntry = pos;
    if (mCurEntry >= mSize)
        mCurEntry = 0;
}

#endif
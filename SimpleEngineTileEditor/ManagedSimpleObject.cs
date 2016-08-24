using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    public class ManagedSimpleObject
    {

        #region DllImports
        //Managed simple object imports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetPosition(IntPtr sObj, ref float x, ref float y, ref float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_Getx(IntPtr sObj, ref float x);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetY(IntPtr sObj, ref float y);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetZ(IntPtr sObj, ref float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetSize(IntPtr sObj, ref float width, ref float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetWidth(IntPtr sObj, ref float width);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetHeight(IntPtr sObj, ref float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_GetOrientation(IntPtr sObj, ref float orientation);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern UInt32 SimpleObject_GetName(IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern String SimpleObject_GetStringName(IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetPosition(IntPtr sObj, float x, float y, float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetX(IntPtr sObj, float x);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetY(IntPtr sObj, float y);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetZ(IntPtr sObj, float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetSize(IntPtr sObj, float width, float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetWidth(IntPtr sObj, float width);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetHeight(IntPtr sObj, float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetOrientation(IntPtr sObj, float orientation);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleObject_SetName(IntPtr sObj, String name);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern UInt32 SimpleObject_GetType(IntPtr sObj);

        //Camera imports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleCamera2D_WorldToScreen(ref float x, ref float y);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleCamera2D_ScreenToWorld(ref float x, ref float y);

        #endregion

        IntPtr _simpleObject;

        public ManagedSimpleObject()
        {

        }
        
        public void SetSimpleObject(IntPtr simpleObject)
        {
            _simpleObject = simpleObject;
        }

        public float positionX
        {
            get
            {
                if (_simpleObject == IntPtr.Zero)
                    return 0.0f;
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleObject, ref x, ref y, ref z);
                float ix = x;
                float iy = y;
                SimpleCamera2D_WorldToScreen(ref ix, ref iy);
                return ix;
            }

            set
            {

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleObject, ref x, ref y, ref z);

                float ix = value;
                float iy = y;
                SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
                SimpleObject_SetX(_simpleObject, ix);
            }
        }

        public float positionY
        {
            get
            {
                if (_simpleObject == IntPtr.Zero)
                    return 0.0f;
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleObject, ref x, ref y, ref z);
                float ix = x;
                float iy = y;
                SimpleCamera2D_WorldToScreen(ref ix, ref iy);
                return iy;
            }

            set
            {

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleObject, ref x, ref y, ref z);

                float ix = value;
                float iy = y;
                SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
                SimpleObject_SetY(_simpleObject, iy);

            }
        }

        public float positionZ
        {
            get
            {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleObject, ref x, ref y, ref z);
                return z;
            }

            set
            {
                SimpleObject_SetZ(_simpleObject, value);
            }
        }

        public float sizeW
        {
            get
            {
                float width = 0.0f;
                SimpleObject_GetWidth(_simpleObject, ref width);
                return width;
            }

            set
            {
                SimpleObject_SetWidth(_simpleObject, value);
            }
        }

        public float sizeH
        {
            get
            {
                float height = 0.0f;
                SimpleObject_GetHeight(_simpleObject, ref height);
                return height;
            }

            set
            {
                SimpleObject_SetHeight(_simpleObject, value);
            }
        }

        public float Orientation
        {
            get
            {
                float orientation = 0.0f;
                SimpleObject_GetOrientation(_simpleObject, ref orientation);
                return orientation;
            }

            set
            {
                float orientation = 0.0f;
                SimpleObject_SetOrientation(_simpleObject, orientation);
            }
        }

        public String Name
        {
            get
            {
                return SimpleObject_GetStringName(_simpleObject);
            }
            set
            {
                SimpleObject_SetName(_simpleObject, value);
            }
        }
    }
}

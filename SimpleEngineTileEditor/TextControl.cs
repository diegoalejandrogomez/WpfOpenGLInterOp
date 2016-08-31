using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    public class TextControl
    {
        #region SimpleTextRenderer Imports
        
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleTextRenderer_Create();

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleTextRenderer_Destroy(IntPtr simpleTextRenderer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleTextRenderer_SetText(IntPtr simpleTextRenderer, String text);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleTextRenderer_SetFontName(IntPtr simpleTextRenderer, String name);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleTextRenderer_SetFontSize(IntPtr simpleTextRenderer, float size);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleTextRenderer_SetColor(IntPtr simpleTextRenderer, int r,int g, int b, int a);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern String SimpleTextRenderer_GetText(IntPtr simpleTextRenderer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern String SimpleTextRenderer_GetFontName(IntPtr simpleTextRenderer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern float SimpleTextRenderer_GetFontSize(IntPtr simpleTextRenderer);

        // [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        //static extern SimpleColor SimpleTextRenderer_GetColor(IntPtr simpleTextRenderer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleScene_AddEntityWithIdx(IntPtr sObj, int nLayer);

        #endregion
        IntPtr simpleTextRenderer;

        public TextControl() {
            simpleTextRenderer = SimpleTextRenderer_Create();
        }

        ~TextControl() {
            SimpleTextRenderer_Destroy(simpleTextRenderer);
        }

        public void AddControl()
        {
            SimpleTextRenderer_SetFontName(simpleTextRenderer, "fonts/arial.ttf");
            SimpleTextRenderer_SetFontSize(simpleTextRenderer, 30);
            SimpleTextRenderer_SetText(simpleTextRenderer, "Dedicated to all the pioneers");
            SimpleTextRenderer_SetColor(simpleTextRenderer, 255,255,255,255);
            SimpleScene_AddEntityWithIdx(simpleTextRenderer, 0);
        }
    }
}

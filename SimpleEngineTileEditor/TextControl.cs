using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;

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

        public void AddControl(int fontSize, string text, string fontFamily, string color)
        {
            string fontsfolder = System.Environment.GetFolderPath(System.Environment.SpecialFolder.Fonts);

            string[] dirs = Directory.GetFiles(fontsfolder, fontFamily + "*");
            if (dirs.Any())
            {
                SimpleTextRenderer_SetFontName(simpleTextRenderer, dirs.First());
            }
            
            SimpleTextRenderer_SetFontSize(simpleTextRenderer, fontSize);
            SimpleTextRenderer_SetText(simpleTextRenderer, text);
            
            string colour = color.TrimStart('#');
            string R = colour.Substring(2, 2);
            string G = colour.Substring(4, 2);
            string B = colour.Substring(6, 2);
            
            SimpleTextRenderer_SetColor(simpleTextRenderer, int.Parse(R, System.Globalization.NumberStyles.HexNumber), int.Parse(G, System.Globalization.NumberStyles.HexNumber), int.Parse(B, System.Globalization.NumberStyles.HexNumber), 255);
            SimpleScene_AddEntityWithIdx(simpleTextRenderer, 0);
        }
    }
}

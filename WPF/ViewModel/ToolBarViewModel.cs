using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using WPF.Infrastructure;

namespace WPF.ViewModel
{
    public class ToolBarViewModel : INotifyPropertyChanged
    {
        public bool DrawLine;

        public bool DrawSquare;

        public event PropertyChangedEventHandler PropertyChanged;

        public void ClearParameters()
        {
            this.DrawSquare = false;
            this.DrawLine = false;
        }

        #region Commands
        private ICommand setDrawLineCommand;

        public ICommand SetDrawLineCommand
        {
            get
            {
                if (setDrawLineCommand == null)
                {

                    setDrawLineCommand = new Command((vm) =>
                    {
                        var originalDrawLine = DrawLine;
                        ClearParameters();
                        DrawLine = !originalDrawLine;
                    });
                }

                return setDrawLineCommand;
            }

            set { }
        }

        private ICommand setDrawSquareCommand;

        public ICommand SetDrawSquareCommand
        {
            get
            {
                if (setDrawSquareCommand == null)
                {

                    setDrawSquareCommand = new Command((vm) =>
                    {
                        var originalDrawSquare = DrawSquare;
                        ClearParameters();
                        DrawSquare = !originalDrawSquare;
                    });
                }

                return setDrawSquareCommand;
            }

            set { }
        }
        #endregion
    }
}

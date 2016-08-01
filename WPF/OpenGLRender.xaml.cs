﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using WPFOpenGLLib;

namespace WPF
{
    /// <summary>
    /// Interaction logic for OpenGLRender.xaml
    /// </summary>
    public partial class OpenGLRender : UserControl
    {

        private readonly System.Windows.Threading.DispatcherTimer updateTimer;

        public OpenGLUserControl OpenGLControl;
        public int Ticks = 1600;

        public OpenGLRender()
        {
            InitializeComponent();
            OpenGLControl = new WPFOpenGLLib.OpenGLUserControl();
            host.Child = OpenGLControl;
            updateTimer = new System.Windows.Threading.DispatcherTimer();
            updateTimer.Interval = new TimeSpan(Ticks);
            updateTimer.Tick += new EventHandler(UpdateTimer_Tick);
            updateTimer.Start();
        }

        private void UpdateTimer_Tick(object sender, EventArgs e)
        {
            OpenGLControl.Invalidate();
        }
    }
}

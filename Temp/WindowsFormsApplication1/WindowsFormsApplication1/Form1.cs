using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /* Esc closes app */
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Escape)
            {
                Close();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void OpenButton_Click_1(object sender, EventArgs e)
        {
            OpenFileDialog fdial = new OpenFileDialog
            {
                InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer),
                Title = "Course schedule",
                Filter = "Microsoft Excel 2007-2013 XML (*.xlsx)|*.xlsx|All Files (*.*)|*.*", //update this as file types are supported
                FilterIndex = 2,
                RestoreDirectory = true
            };

            // Fill DataTable with .xlsb file
            if (fdial.ShowDialog() == DialogResult.OK)
            {
                if (fdial.FileName != null)
                {
                    try
                    {
                        string filename = fdial.FileName.ToString();
                        string connectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = " + filename + ";" +
                                                  "Extended Properties=\"Excel 12.0 Xml;HDR=YES;IMEX=1\""; //connectionstrings.com


                        OleDbConnection connection = new OleDbConnection(connectionString); // establish link to file
                        OleDbDataAdapter command = new OleDbDataAdapter("select * from [Sheet1$]", connection); // select every cell on Sheet1
                        DataSet ds = new DataSet(); // initialize dataset for data grid
                        command.Fill(ds); // fill data grid
                        scheduleDataGridView.DataSource = ds.Tables[0];
                        connection.Close();
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex);
                        MessageBox.Show(ex.ToString());
                    }
                }
            }
        }
    }
}

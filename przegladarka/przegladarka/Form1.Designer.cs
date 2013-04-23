namespace przegladarka
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.folder_tree = new System.Windows.Forms.TreeView();
            this.explorer_view = new System.Windows.Forms.ListView();
            this.path_textbox = new System.Windows.Forms.TextBox();
            this.Dysk1 = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // folder_tree
            // 
            this.folder_tree.Location = new System.Drawing.Point(12, 38);
            this.folder_tree.Name = "folder_tree";
            this.folder_tree.Size = new System.Drawing.Size(143, 320);
            this.folder_tree.TabIndex = 0;
            // 
            // explorer_view
            // 
            this.explorer_view.Location = new System.Drawing.Point(161, 38);
            this.explorer_view.Name = "explorer_view";
            this.explorer_view.Size = new System.Drawing.Size(785, 320);
            this.explorer_view.TabIndex = 1;
            this.explorer_view.UseCompatibleStateImageBehavior = false;
            this.explorer_view.SelectedIndexChanged += new System.EventHandler(this.explorer_view_SelectedIndexChanged);
            // 
            // path_textbox
            // 
            this.path_textbox.Location = new System.Drawing.Point(161, 12);
            this.path_textbox.Name = "path_textbox";
            this.path_textbox.Size = new System.Drawing.Size(785, 20);
            this.path_textbox.TabIndex = 2;
            // 
            // Dysk1
            // 
            this.Dysk1.FormattingEnabled = true;
            this.Dysk1.Location = new System.Drawing.Point(12, 12);
            this.Dysk1.Name = "Dysk1";
            this.Dysk1.Size = new System.Drawing.Size(143, 21);
            this.Dysk1.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(958, 447);
            this.Controls.Add(this.Dysk1);
            this.Controls.Add(this.path_textbox);
            this.Controls.Add(this.explorer_view);
            this.Controls.Add(this.folder_tree);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView folder_tree;
        private System.Windows.Forms.ListView explorer_view;
        private System.Windows.Forms.TextBox path_textbox;
        private System.Windows.Forms.ComboBox Dysk1;
    }
}


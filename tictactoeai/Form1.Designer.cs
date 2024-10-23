namespace AI_07
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.Button[,] buttons = new System.Windows.Forms.Button[3, 3];
        private System.Windows.Forms.Label statusLabel;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.statusLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();

            // Initialize buttons
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    this.buttons[i, j] = new System.Windows.Forms.Button();
                    this.buttons[i, j].Size = new System.Drawing.Size(100, 100);
                    this.buttons[i, j].Location = new System.Drawing.Point(100 * j, 100 * i);
                    this.buttons[i, j].Click += new System.EventHandler(this.Button_Click);
                    this.Controls.Add(this.buttons[i, j]);
                }
            }

            // Status Label
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(20, 320);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(35, 13);
            this.statusLabel.TabIndex = 0;
            this.statusLabel.Text = "Turn: Human";
            this.Controls.Add(this.statusLabel);

            // Form1
            this.ClientSize = new System.Drawing.Size(320, 350);
            this.Name = "Form1";
            this.Text = "Tic-Tac-Toe";
            this.ResumeLayout(false);
            this.PerformLayout();
        }
    }
}

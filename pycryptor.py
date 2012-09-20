#!/usr/bin/python

import os
import wx # The GUI API
import vcryptor # The c code extension


###############################################################################
class MainWindow(wx.Frame):
    """
        A program that uses the vcryptor module to encrypt and decrypt a file.
    """
#______________________________________________________________________________
    def __init__(self, parent, title):

        # Initialize the parent frame
        # *** A -1 specifies default parameter
        wx.Frame.__init__(self, parent, title=title, size = (500, 125))
        self.SetIcon(wx.Icon('vcryptor_icon.png', wx.BITMAP_TYPE_PNG))

        # A status bar in the bottom of the window
        self.CreateStatusBar()

        # Make menus for the menubar
        helpmenu = wx.Menu()

        # Make the menu items
        menuAbout = helpmenu.Append(wx.ID_ABOUT, "About",
                                   " Information about this program")
        menuUsage = helpmenu.Append(-1, "Usage","How to use pycryptor")

        # Create the menubar
        menuBar = wx.MenuBar()
        menuBar.Append(helpmenu, "Help")
        self.SetMenuBar(menuBar)

        # Set menubar events
        self.Bind(wx.EVT_MENU, self.OnAbout, menuAbout)
        self.Bind(wx.EVT_MENU, self.OnHelp, menuUsage)
        
        # An blank object for spacing
        space = wx.StaticText(self, -1, "")

        # The file browsing panel
        filePanel = wx.Panel(self, -1)
        
        fileBoxLabel = wx.StaticText(filePanel, -1, "File Name")
        self.fileBox = wx.TextCtrl(filePanel, style=wx.TE_LEFT)
        
        browse_button = wx.Button(filePanel, id=-1, label="Browse")
        self.Bind(wx.EVT_BUTTON, self.OnBrowse, browse_button)
        
        fileSizer = wx.BoxSizer(wx.HORIZONTAL)
        fileSizer.Add(space,1,wx.ALIGN_CENTER)
        fileSizer.Add(fileBoxLabel,4,wx.ALIGN_CENTER)
        fileSizer.Add(self.fileBox,6,wx.ALIGN_CENTER)
        fileSizer.Add(browse_button,3,wx.ALIGN_CENTER)
        fileSizer.Add(space,4,wx.ALIGN_CENTER)
        
        filePanel.SetSizer(fileSizer)
        filePanel.SetAutoLayout(True)
        
        
        # The password panel
        pswdPanel = wx.Panel(self, -1)
        
        pswdBoxLabel = wx.StaticText(pswdPanel, -1, "Password")
        self.pswdBox = wx.TextCtrl(pswdPanel, style=wx.TE_PASSWORD)
        
        encrypt_button = wx.Button(pswdPanel, id=-1, label="Encrypt")
        self.Bind(wx.EVT_BUTTON, self.OnEncrypt, encrypt_button)
        
        decrypt_button = wx.Button(pswdPanel, id=-1, label="Decrypt")
        self.Bind(wx.EVT_BUTTON, self.OnDecrypt, decrypt_button)
        
        pswdSizer = wx.BoxSizer(wx.HORIZONTAL)
        pswdSizer.Add(space,1,wx.ALIGN_CENTER)
        pswdSizer.Add(pswdBoxLabel,4,wx.ALIGN_CENTER)
        pswdSizer.Add(self.pswdBox,6,wx.ALIGN_CENTER)
        pswdSizer.Add(encrypt_button,3,wx.ALIGN_CENTER)
        pswdSizer.Add(decrypt_button,3,wx.ALIGN_CENTER)
        pswdSizer.Add(space,1,wx.ALIGN_CENTER)
        
        pswdPanel.SetSizer(pswdSizer)
        pswdPanel.SetAutoLayout(True)
        
        # Create the options panel
        optionPanel = wx.Panel(self, -1)
        self.showCB = wx.CheckBox(optionPanel, -1, "Show Password")
        self.showCB.SetValue(False)
        
        wx.EVT_CHECKBOX(self, self.showCB.GetId(), self.ShowPswd)
        
        optionSizer = wx.BoxSizer(wx.HORIZONTAL)
        optionSizer.Add(space,1,wx.ALIGN_CENTER)
        optionSizer.Add(self.showCB,16,wx.ALIGN_CENTER)
        optionSizer.Add(space,1,wx.ALIGN_CENTER)
        
        optionPanel.SetSizer(optionSizer)
        pswdPanel.SetAutoLayout(True)
        

        # Add the file and password panels
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.sizer.Add(filePanel, 2, wx.EXPAND)
        self.sizer.Add(pswdPanel, 2, wx.EXPAND)
        self.sizer.Add(optionPanel, 1, wx.EXPAND)

        # Layout sizers
        self.SetSizer(self.sizer)
        self.SetAutoLayout(True)

        # Make the frame visible
        self.Show(True)
    
    def OnAbout(self, event):
        """ A message dialog box with an OK button.

            wx.OK is a standard ID in wxWidgets
        """
        msg  = "This is a simple tool that lets you encrypt a file with a\n"
        msg += "polyalphebetic cypher that's been extended to all ASCII\n"
        msg += "characters. It is by no means secure, but it was fun to make\n"
        msg += "and can be fun to use.\n"
        msg += "\n"
        msg += "PLEASE NOTE\n"
        msg += "This tool will edit the binary of the file that it encrypts\n"
        msg += "or decrypts. If you forget the password or the order that you\n"
        msg += "encrypt and decrypt a file, you will have to either break the\n"
        msg += "encryption algorithm or deal with the fact that your file has\n"
        msg += "been turned to garbage.\n"
        msg += "\n"
        msg += "Have fun and be safe!"
        title = "About pycryptor"
        dlgID = wx.OK
        dlg = wx.MessageDialog(self, msg, title, dlgID)
        dlg.ShowModal() # Show it
        dlg.Destroy() # finally destroy it when finished
        
        
    def OnHelp(self, event):
        """ A message dialog box with an OK button.

            wx.OK is a standard ID in wxWidgets
        """
        msg  = "To encrypt or decrypt a file, simply select the file, enter a\n"
        msg += "password, and then click on \"Encrypt\", or \"Decrypt\"."
        title = "Using pycryptor"
        dlgID = wx.OK
        dlg = wx.MessageDialog(self, msg, title, dlgID)
        dlg.ShowModal() # Show it
        dlg.Destroy() # finally destroy it when finished
    
    def OnBrowse(self, event):
        """
        Browse for a file
        """
        self.dirname = ''
        dlg = wx.FileDialog(self, "Choose a file",
                            self.dirname, "", "*.*", wx.OPEN)
                            
        if  dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename()
            self.dirname = dlg.GetDirectory()
            self.fileBox.SetValue(self.dirname + "/" + self.filename)
            dlg.Destroy()
    
    def ShowPswd(self, event):
        """ 
        This changes the style of the password box (may not work on Windows)
        """
        if self.showCB.GetValue():
            self.pswdBox.SetWindowStyle(wx.TE_LEFT)
        else:
            self.pswdBox.SetWindowStyle(wx.TE_PASSWORD)

    def TestOpen(self, FileName):
        try:
            f = open(FileName)
            f.close()
            return True
        except Exception:
            print "ERROR: could not open", FileName
            self.StatusBar.SetStatusText("ERROR: could not open "+FileName)
            return False
    
    def OnEncrypt(self, event):
        password = self.pswdBox.GetValue()
        fileName = self.fileBox.GetValue()
        if self.TestOpen(fileName):
            self.StatusBar.SetStatusText("Encrypting...")
            vcryptor.cryption(fileName,password,True)
            self.StatusBar.SetStatusText("Encryption Successful!")
    
    def OnDecrypt(self, event):
        password = self.pswdBox.GetValue()
        fileName = self.fileBox.GetValue()
        if self.TestOpen(fileName):
            self.StatusBar.SetStatusText("Decrypting...")
            vcryptor.cryption(fileName,password,False)
            self.StatusBar.SetStatusText("Decryption Successful!")



###############################################################################
# Create an instance of the application without redirecting output to a window
app = wx.App(False)

# Create the main window
frame = MainWindow(None, 'pycryptor')
frame.Center()

# Start the application loop
app.MainLoop()


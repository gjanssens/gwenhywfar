/***************************************************************************
    begin       : Sun May 16 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/



/*
 * Note: This is a special use case for gtk_notebook.
 * To use it as a WidgetStack we have to disable drawing od tabs
 * and borders by calling:
 * - gtk_notebook_set_show_tabs(GTK_NOTEBOOK(g), FALSE);
 * - gtk_notebook_set_show_border(GTK_NOTEBOOK(g), FALSE);
 *
 */



static GWENHYWFAR_CB
int Gtk2Gui_WStack_SetIntProperty(GWEN_WIDGET *w,
                                  GWEN_DIALOG_PROPERTY prop,
                                  int index,
                                  int value,
                                  int doSignal)
{
  GtkWidget *g;

  g=GTK_WIDGET(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  switch (prop) {
  case GWEN_DialogProperty_Enabled:
    gtk_widget_set_sensitive(GTK_WIDGET(g), (value==0)?FALSE:TRUE);
    return 0;

  case GWEN_DialogProperty_Focus:
    gtk_widget_grab_focus(GTK_WIDGET(g));
    return 0;

  case GWEN_DialogProperty_Value:
    gtk_notebook_set_current_page(GTK_NOTEBOOK(g), value);
    return 0;

  default:
    break;
  }

  DBG_WARN(GWEN_LOGDOMAIN,
           "Function is not appropriate for this type of widget (%s)",
           GWEN_Widget_Type_toString(GWEN_Widget_GetType(w)));
  return GWEN_ERROR_INVALID;
}




static GWENHYWFAR_CB
int Gtk2Gui_WStack_GetIntProperty(GWEN_WIDGET *w,
                                  GWEN_DIALOG_PROPERTY prop,
                                  int index,
                                  int defaultValue)
{
  GtkWidget *g;

  g=GTK_WIDGET(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  switch (prop) {
  case GWEN_DialogProperty_Enabled:
    return (gtk_widget_get_sensitive(GTK_WIDGET(g))==TRUE)?1:0;

  case GWEN_DialogProperty_Focus:
    return (gtk_widget_has_focus(GTK_WIDGET(g))==TRUE)?1:0;
    return 0;

  case GWEN_DialogProperty_Value:
    return gtk_notebook_get_current_page(GTK_NOTEBOOK(g));

  default:
    break;
  }

  DBG_WARN(GWEN_LOGDOMAIN,
           "Function is not appropriate for this type of widget (%s)",
           GWEN_Widget_Type_toString(GWEN_Widget_GetType(w)));
  return defaultValue;
}



static GWENHYWFAR_CB
int Gtk2Gui_WStack_SetCharProperty(GWEN_WIDGET *w,
                                   GWEN_DIALOG_PROPERTY prop,
                                   int index,
                                   const char *value,
                                   int doSignal)
{
  GtkWidget *g;

  g=GTK_WIDGET(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  DBG_WARN(GWEN_LOGDOMAIN,
           "Function is not appropriate for this type of widget (%s)",
           GWEN_Widget_Type_toString(GWEN_Widget_GetType(w)));
  return GWEN_ERROR_INVALID;
}



static GWENHYWFAR_CB
const char *Gtk2Gui_WStack_GetCharProperty(GWEN_WIDGET *w,
                                           GWEN_DIALOG_PROPERTY prop,
                                           int index,
                                           const char *defaultValue)
{
  GtkWidget *g;

  g=GTK_WIDGET(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  DBG_WARN(GWEN_LOGDOMAIN,
           "Function is not appropriate for this type of widget (%s)",
           GWEN_Widget_Type_toString(GWEN_Widget_GetType(w)));
  return defaultValue;
}



static GWENHYWFAR_CB
int Gtk2Gui_WStack_AddChildGuiWidget(GWEN_WIDGET *w, GWEN_WIDGET *wChild)
{
  GtkWidget *g;
  GtkWidget *gChild;

  g=GTK_WIDGET(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  gChild=GTK_WIDGET(GWEN_Widget_GetImplData(wChild, GTK2_DIALOG_WIDGET_REAL));
  assert(gChild);

  gtk_notebook_append_page(GTK_NOTEBOOK(g), gChild, NULL);

  return 0;
}



int Gtk2Gui_WStack_Setup(GWEN_WIDGET *w)
{
  GtkWidget *g;
  uint32_t flags;
  GWEN_WIDGET *wParent;

  flags=GWEN_Widget_GetFlags(w);
  wParent=GWEN_Widget_Tree_GetParent(w);

  g=gtk_notebook_new();
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(g), FALSE);
  gtk_notebook_set_show_border(GTK_NOTEBOOK(g), FALSE);

  GWEN_Widget_SetImplData(w, GTK2_DIALOG_WIDGET_REAL, (void *) g);
  GWEN_Widget_SetImplData(w, GTK2_DIALOG_WIDGET_CONTENT, (void *) g);

  GWEN_Widget_SetSetIntPropertyFn(w, Gtk2Gui_WStack_SetIntProperty);
  GWEN_Widget_SetGetIntPropertyFn(w, Gtk2Gui_WStack_GetIntProperty);
  GWEN_Widget_SetSetCharPropertyFn(w, Gtk2Gui_WStack_SetCharProperty);
  GWEN_Widget_SetGetCharPropertyFn(w, Gtk2Gui_WStack_GetCharProperty);
  GWEN_Widget_SetAddChildGuiWidgetFn(w, Gtk2Gui_WStack_AddChildGuiWidget);

  if (wParent)
    GWEN_Widget_AddChildGuiWidget(wParent, w);

  return 0;
}



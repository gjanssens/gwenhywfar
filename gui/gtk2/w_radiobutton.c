/***************************************************************************
    begin       : Mon Jul 12 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/





static GWENHYWFAR_CB
int Gtk2Gui_WRadioButton_SetIntProperty(GWEN_WIDGET *w,
                                        GWEN_DIALOG_PROPERTY prop,
                                        int index,
                                        int value,
                                        int doSignal)
{
  GtkButton *g;

  g=GTK_BUTTON(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  switch (prop) {
  case GWEN_DialogProperty_Enabled:
    gtk_widget_set_sensitive(GTK_WIDGET(g), (value==0)?FALSE:TRUE);
    return 0;

  case GWEN_DialogProperty_Focus:
    gtk_widget_grab_focus(GTK_WIDGET(g));
    return 0;

  case GWEN_DialogProperty_Width:
  case GWEN_DialogProperty_Height:
    /* just ignore these for now */
    return 0;

  case GWEN_DialogProperty_Value:
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g), (value==0)?FALSE:TRUE);
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
int Gtk2Gui_WRadioButton_GetIntProperty(GWEN_WIDGET *w,
                                        GWEN_DIALOG_PROPERTY prop,
                                        int index,
                                        int defaultValue)
{
  GtkButton *g;

  g=GTK_BUTTON(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  switch (prop) {
  case GWEN_DialogProperty_Enabled:
    return (gtk_widget_get_sensitive(GTK_WIDGET(g))==TRUE)?1:0;

  case GWEN_DialogProperty_Focus:
    return (gtk_widget_has_focus(GTK_WIDGET(g))==TRUE)?1:0;

  case GWEN_DialogProperty_Width:
  case GWEN_DialogProperty_Height:
    /* just ignore these for now */
    return 0;

  case GWEN_DialogProperty_Value:
    return (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g))==TRUE)?1:0;

  default:
    break;
  }

  DBG_WARN(GWEN_LOGDOMAIN,
           "Function is not appropriate for this type of widget (%s)",
           GWEN_Widget_Type_toString(GWEN_Widget_GetType(w)));
  return defaultValue;
}



static GWENHYWFAR_CB
int Gtk2Gui_WRadioButton_SetCharProperty(GWEN_WIDGET *w,
                                         GWEN_DIALOG_PROPERTY prop,
                                         int index,
                                         const char *value,
                                         int doSignal)
{
  GtkButton *g;

  g=GTK_BUTTON(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  switch (prop) {
  case GWEN_DialogProperty_Title:
    gtk_button_set_label(g, value);
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
const char *Gtk2Gui_WRadioButton_GetCharProperty(GWEN_WIDGET *w,
                                                 GWEN_DIALOG_PROPERTY prop,
                                                 int index,
                                                 const char *defaultValue)
{
  GtkButton *g;

  g=GTK_BUTTON(GWEN_Widget_GetImplData(w, GTK2_DIALOG_WIDGET_REAL));
  assert(g);

  switch (prop) {
  case GWEN_DialogProperty_Title:
    return gtk_button_get_label(g);
  default:
    break;
  }

  DBG_WARN(GWEN_LOGDOMAIN,
           "Function is not appropriate for this type of widget (%s)",
           GWEN_Widget_Type_toString(GWEN_Widget_GetType(w)));
  return defaultValue;
}



static void Gtk2Gui_WRadioButton_Toggled_handler(GtkButton *button, gpointer data)
{
  GWEN_WIDGET *w;
  int rv;

  w=data;
  assert(w);
  rv=GWEN_Dialog_EmitSignal(GWEN_Widget_GetDialog(w),
                            GWEN_DialogEvent_TypeActivated,
                            GWEN_Widget_GetName(w));
  if (rv==GWEN_DialogEvent_ResultAccept)
    Gtk2Gui_Dialog_Leave(GWEN_Widget_GetTopDialog(w), 1);
  else if (rv==GWEN_DialogEvent_ResultReject)
    Gtk2Gui_Dialog_Leave(GWEN_Widget_GetTopDialog(w), 0);
}



int Gtk2Gui_WRadioButton_Setup(GWEN_WIDGET *w)
{
  GtkWidget *g;
  const char *s;
  uint32_t flags;
  GWEN_WIDGET *wParent;
  GWEN_WIDGET *wT;
  gulong toggled_handler_id;
  int groupId;

  flags=GWEN_Widget_GetFlags(w);
  wParent=GWEN_Widget_Tree_GetParent(w);
  groupId=GWEN_Widget_GetGroupId(w);

  s=GWEN_Widget_GetText(w, 0);

  /* create widget */
  if (s && *s)
    g=gtk_radio_button_new_with_mnemonic(NULL, s);
  else
    g=gtk_radio_button_new(NULL);

  /* get root widget */
  wT=wParent;
  while (GWEN_Widget_Tree_GetParent(wT))
    wT=GWEN_Widget_Tree_GetParent(wT);

  /* get first radio button of the same group */
  while (wT) {
    if ((GWEN_Widget_GetType(wT)==GWEN_Widget_TypeRadioButton) &&
        GWEN_Widget_GetGroupId(wT)==groupId)
      break;
    wT=GWEN_Widget_Tree_GetBelow(wT);
  }
  if (wT && wT!=w) {
    GSList *grp;

    grp=gtk_radio_button_get_group(GTK_RADIO_BUTTON(GWEN_Widget_GetImplData(wT, GTK2_DIALOG_WIDGET_REAL)));
    gtk_radio_button_set_group(GTK_RADIO_BUTTON(g), grp);
  }

  /* set pointers */
  GWEN_Widget_SetImplData(w, GTK2_DIALOG_WIDGET_REAL, (void *) g);
  GWEN_Widget_SetImplData(w, GTK2_DIALOG_WIDGET_CONTENT, (void *) g);

  GWEN_Widget_SetSetIntPropertyFn(w, Gtk2Gui_WRadioButton_SetIntProperty);
  GWEN_Widget_SetGetIntPropertyFn(w, Gtk2Gui_WRadioButton_GetIntProperty);
  GWEN_Widget_SetSetCharPropertyFn(w, Gtk2Gui_WRadioButton_SetCharProperty);
  GWEN_Widget_SetGetCharPropertyFn(w, Gtk2Gui_WRadioButton_GetCharProperty);

  toggled_handler_id=g_signal_connect(g,
                                      "toggled",
                                      G_CALLBACK(Gtk2Gui_WRadioButton_Toggled_handler),
                                      w);

  if (wParent)
    GWEN_Widget_AddChildGuiWidget(wParent, w);

  return 0;
}



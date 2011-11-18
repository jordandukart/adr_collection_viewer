/*
 * File: EditObjectWindow.ui.js
 * Date: Fri Nov 18 2011 13:39:59 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

EditObjectWindowUi = Ext.extend(Ext.Window, {
    title: 'Edit Object',
    width: 542,
    height: 164,
    layout: 'fit',
    cls: 'adr-clear',
    id: 'adr-edit-obj-window',
    initComponent: function() {
        this.items = [
            {
                xtype: 'form',
                headerAsText: false,
                frame: true,
                items: [
                    {
                        xtype: 'textfield',
                        fieldLabel: 'Label',
                        anchor: '100%',
                        name: 'label'
                    },
                    {
                        xtype: 'textfield',
                        fieldLabel: 'Owner',
                        anchor: '100%',
                        name: 'owner'
                    },
                    {
                        xtype: 'combo',
                        fieldLabel: 'State',
                        anchor: '100%',
                        store: 'State',
                        mode: 'local',
                        allowBlank: false,
                        name: 'state',
                        displayField: 'type',
                        valueField: 'value',
                        submitValue: true,
                        editable: false,
                        triggerAction: 'all',
                        forceSelection: true
                    }
                ],
                fbar: {
                    xtype: 'toolbar',
                    items: [
                        {
                            xtype: 'button',
                            text: 'Save'
                        }
                    ]
                }
            }
        ];
        EditObjectWindowUi.superclass.initComponent.call(this);
    }
});

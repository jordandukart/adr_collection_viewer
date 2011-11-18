/*
 * File: Manage.ui.js
 * Date: Fri Nov 18 2011 13:39:59 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

ManageUi = Ext.extend(Ext.Panel, {
    title: 'Manage',
    layout: 'border',
    border: false,
    height: 900,
    initComponent: function() {
        this.defaults = {
            split: true
        };
        this.items = [
            {
                xtype: 'panel',
                title: 'Object Properties',
                frame: true,
                region: 'north',
                height: 140,
                id: 'adr-manage-object-properties',
                items: [
                    {
                        xtype: 'dataview',
                        itemSelector: 'div',
                        store: 'ObjectProperties',
                        tpl: [
                            '<tpl for=".">',
                            '<table>',
                            ' <tr><th>Label: </th><td>{label}</td></tr>',
                            ' <tr><th>Created: </th><td>{created}</td></tr>',
                            ' <tr><th>Modified: </th><td>{modified}</td></tr>',
                            ' <tr><th>Owner: </th><td>{owner}</td></tr>',
                            ' <tr><th>State: </th><td>{state}</td></tr>',
                            '</table>',
                            '</tpl>'
                        ]
                    }
                ],
                fbar: {
                    xtype: 'toolbar',
                    items: [
                        {
                            xtype: 'button',
                            text: 'Edit Object',
                            id: 'adr-manage-edit-object'
                        },
                        {
                            xtype: 'button',
                            text: 'Edit Permissions',
                            id: 'adr-manage-edit-object-permissions'
                        },
                        {
                            xtype: 'button',
                            text: 'Edit Child Permissions',
                            id: 'adr-manage-edit-child-permissions'
                        },
                        {
                            xtype: 'button',
                            text: 'Delete Object',
                            id: 'adr-manage-delete-object'
                        }
                    ]
                }
            },
            {
                xtype: 'panel',
                title: 'Detailed Information',
                width: 200,
                html: 'Select a Datastream',
                region: 'east',
                tpl: [
                    '<img src="{img_url}" style="display:block;margin-right:auto;margin-left:auto;"></img>',
                    '<div style="text-align:center;">{label}</div>',
                    '<div style="text-align:center;">{dsid}</div>'
                ],
                frame: true,
                id: 'adr-manage-detailed-info'
            },
            {
                xtype: 'panel',
                title: 'Manage Collection Datastreams',
                region: 'center',
                width: 100,
                id: 'adr-manage-datastreams',
                fbar: {
                    xtype: 'paging',
                    store: 'Datastreams',
                    id: 'adr-manage-datastreams-pager'
                },
                items: [
                    {
                        xtype: 'listview',
                        store: 'Datastreams',
                        loadingText: 'Loading Please Wait...',
                        singleSelect: true,
                        id: 'adr-edit-file-list',
                        columns: [
                            {
                                xtype: 'lvcolumn',
                                header: 'Label',
                                width: 0.25,
                                dataIndex: 'label'
                            },
                            {
                                xtype: 'lvcolumn',
                                header: 'Datastream ID',
                                dataIndex: 'dsid'
                            },
                            {
                                xtype: 'lvcolumn',
                                header: 'Mime Type',
                                dataIndex: 'mime'
                            }
                        ]
                    }
                ],
                tbar: {
                    xtype: 'toolbar',
                    items: [
                        {
                            xtype: 'button',
                            text: 'Add',
                            cls: 'x-btn-text-icon',
                            iconCls: 'adr-add-file-icon',
                            width: 50,
                            id: 'adr-edit-file-add'
                        },
                        {
                            xtype: 'tbseparator'
                        },
                        {
                            xtype: 'button',
                            text: 'Edit',
                            cls: 'x-btn-text-icon',
                            iconCls: 'adr-edit-file-icon',
                            width: 50,
                            id: 'adr-edit-file-edit'
                        },
                        {
                            xtype: 'tbseparator'
                        },
                        {
                            xtype: 'button',
                            text: 'Download',
                            cls: 'x-btn-text-icon',
                            iconCls: 'adr-download-file-icon',
                            width: 50,
                            id: 'adr-edit-file-download'
                        },
                        {
                            xtype: 'tbseparator'
                        },
                        {
                            xtype: 'button',
                            text: 'Delete',
                            cls: 'x-btn-text-icon',
                            iconCls: 'adr-delete-file-icon',
                            width: 50,
                            id: 'adr-edit-file-delete'
                        }
                    ]
                }
            }
        ];
        ManageUi.superclass.initComponent.call(this);
    }
});

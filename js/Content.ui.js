/*
 * File: Content.ui.js
 * Date: Wed Apr 13 2011 15:53:45 GMT-0300 (ADT)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

ContentUi = Ext.extend(Ext.Panel, {
    title: 'Content',
    height: 900,
    layout: 'fit',
    initComponent: function() {
        this.tbar = {
            xtype: 'toolbar',
            items: [
                {
                    xtype: 'label',
                    text: 'Filter: '
                },
                {
                    xtype: 'spacer',
                    width: 10
                },
                {
                    xtype: 'cycle',
                    showText: true,
                    minWidth: 75,
                    prependText: 'Show ',
                    id: 'adr-content-filter',
                    items: [
                        {
                            xtype: 'menucheckitem',
                            text: 'All Content',
                            checked: true
                        },
                        {
                            xtype: 'menucheckitem',
                            text: 'Only Collections'
                        },
                        {
                            xtype: 'menucheckitem',
                            text: 'Only Objects'
                        }
                    ]
                },
                {
                    xtype: 'spacer',
                    width: 10
                },
                {
                    xtype: 'label',
                    text: 'Search: '
                },
                {
                    xtype: 'tbspacer',
                    width: 10
                },
                {
                    xtype: 'trigger',
                    id: 'adr-content-search-text'
                },
                {
                    xtype: 'tbspacer',
                    width: 5
                },
                {
                    xtype: 'cycle',
                    showText: true,
                    id: 'adr-content-search-type',
                    items: [
                        {
                            xtype: 'menucheckitem',
                            text: 'Starts With',
                            checked: true
                        },
                        {
                            xtype: 'menucheckitem',
                            text: 'Contains'
                        }
                    ]
                }
            ]
        };
        this.items = [
            {
                xtype: 'panel',
                frame: true,
                id: 'adr-content-panel',
                items: [
                    {
                        xtype: 'dataview',
                        itemSelector: 'div',
                        store: 'CollectionMembers',
                        tpl: [
                            '<tpl for=".">',
                            '<div class="adr-content-item">',
                            '<table>',
                            '<tr><a href=\'{url}\'><th class="adr-content-item-icon-block"><img src="{img_url}" class="adr-content-item-icon"/></th></a><th><a href=\'{url}\'><h2 class="adr-content-item-title">{title}</h2></a></th></tr>',
                            '<tr><td/><td class="adr-content-item-description">{[fm.ellipsis(values.description, 350, true)]} <a href=\'{url}\' class="adr-content-item-link"> [Click for more]</a></td></tr>',
                            '</table>',
                            '</div>',
                            '</tpl>'
                        ],
                        loadingText: 'Loading Please Wait...'
                    }
                ],
                fbar: {
                    xtype: 'paging',
                    store: 'CollectionMembers',
                    pageSize: 7
                }
            }
        ];
        ContentUi.superclass.initComponent.call(this);
    }
});

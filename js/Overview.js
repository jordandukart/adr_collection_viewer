/*
 * File: Overview.js
 * Date: Thu Apr 07 2011 13:09:49 GMT-0300 (ADT)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be generated the first time you export.
 *
 * You should implement event handling and custom methods in this
 * class.
 */

Overview = Ext.extend(OverviewUi, {
    initComponent: function() {
        Overview.superclass.initComponent.call(this);
        var link = Ext.get('adr-show-overview-link');
        link.on('click', function() {
            var viewer = Ext.getCmp('adr-collection-tabpanel');
            viewer.setActiveTab(0);
        });
    }
});
Ext.reg('overview', Overview);
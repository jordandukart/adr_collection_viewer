<?php

// $Id$

/**
 * @file
 *
 */

/**
 *
 */
class ADRCollection {

  /**
   * The pid of the collection this viewer will show.
   * @var string
   */
  protected $pid;
  /**
   * The path to this module.
   * 
   * @var string
   */
  protected $path;
  /**
   * The fedora object defined by $pid.
   * 
   * @var Fedora_Item 
   */
  protected $item;
  /**
   *
   * @var Collection
   */
  protected $collection;

  /**
   * Create the collection viewer.
   * 
   * @param string $pid
   *   The collection this viewer will show, if NULL is specified, the sites default top collection will
   *   be shown.
   */
  public function __construct($pid = NULL) {
    $this->pid = isset($pid) ? $pid : variable_get('fedora_repository_pid', 'islandora:top');
    module_load_include('inc', 'adr_collection_viewer', 'Collection');
    $this->collection = new Collection($this->pid);
    $this->path = drupal_get_path('module', 'adr_collection_viewer');
  }

  /**
   *
   */
  private function includeRequiredScripts() {
    $path = drupal_get_path('module', 'adr_collection_viewer');
    drupal_add_css("$path/stylesheets/Clear.css", 'theme', 'all');
    module_load_include('module', 'ext', 'ext');
    ext_load_library();
    drupal_add_css("$path/stylesheets/ADRCollection.css", 'theme', 'all');

    $data_stores = array(
      'Datastreams.js',
      'ControlGroups.js',
      'MIMETypes.js',
      'CollectionProperties.js',
      'CollectionMembers.js'
    );

    $custom_components = array(
      'FileUploadField.ui.js',
      'FileUploadField.js',
    );

    $main_viewer = array(
      'ADRCollectionViewer.ui.js',
      'ADRCollectionViewer.js',
      'Content.ui.js',
      'Content.js',
    );

    drupal_add_js("$path/js/IncludeFirst.js");
    $this->includeScripts($data_stores, $path);
    $this->includeScripts($custom_components, $path);
    $this->includeScripts($main_viewer, $path);
    if ($this->canShowOverviewPanel()) {
      $this->includeOverviewPanel();
    }
    if ($this->canShowManagePanel()) {
      $this->includeManagePanel();
    }
    drupal_add_js("$path/js/ADRCollection.js");
  }

  /**
   * Can we show the overview panel.
   *
   * Checks to see if this object has a MODS datastream if so the overview panel can be included.
   *
   * @return boolean
   */
  private function canShowOverviewPanel() {
    return $this->collection->hasMetadata();
  }

  /**
   * Includes the required javascript to render the manage panel.
   */
  private function includeOverviewPanel() {
    drupal_add_js("{$this->path}/js/Overview.ui.js");
    drupal_add_js("{$this->path}/js/Overview.js");
  }

  /**
   * Can we show the manage panel.
   *
   * Checks user permissions to decide if the user can manage this collection.
   * 
   * @return boolean
   */
  private function canShowManagePanel() {
    return user_access('purge objects and datastreams')
    && user_access('add fedora datastreams')
    && user_access('edit fedora meta data');
  }

  /**
   * Includes the required javascript to render the manage panel.
   */
  private function includeManagePanel() {
    drupal_add_js("{$this->path}/js/Manage.ui.js");
    drupal_add_js("{$this->path}/js/Manage.js");
    drupal_add_js("{$this->path}/js/AddDatastream.ui.js");
    drupal_add_js("{$this->path}/js/AddDatastream.js");
  }

  /**
   *
   * @param array $scripts
   * @param string $path
   */
  private function includeScripts($scripts, $path) {
    foreach ($scripts as $file) {
      drupal_add_js("$path/js/$file");
    }
  }

  /**
   * Gets the html for this collections title.
   *
   * @return string
   */
  private function getCollectionTitle() {
    $label = $this->collection->getLabel();
    return <<<EOT
    <h1 class="adr-collection-title">{$label}</h1>
EOT;
  }

  /**
   * Gets the html for this collections description.
   *
   * @return string
   */
  private function getCollectionDescription() {
    $description = $this->collection->getDescription();
    if (empty($description)) {
      $description = "Since most collections don't have a description I'm putting the Lorem ipsum, here to give a view of what it will look like with descriptions. Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
      $description = "$description $description";
    }
    $description = substr($description, 0, 350);
    if (isset($description)) {
      return "<table class='adr-collection-description'>
              <tr><th class='adr-collection-description'>Description</th><td class='adr-collection-description'>{$description}<a href='#adr-collection-title' id='adr-show-overview-link'> [Click for more ...]</a></td></tr>
              </table>";
    }
    return NULL;
  }

  /**
   *
   */
  public function render() {
    $this->includeRequiredScripts(); // Javascript all the way!
    $title = $this->getCollectionTitle();
    $description = $this->getCollectionDescription();
    return <<<EOT
    $title
    $description
    <div id='content-fedora'>
      
    </div>
EOT;
  }

}
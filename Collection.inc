<?php

// $Id$

/**
 * @file
 *
 */
class Collection {

  /**
   * The pid of this Collection.
   * 
   * @var string
   */
  protected $pid;
  /**
   * This collections fedora object.
   * @var Fedora_Item
   */
  protected $item;
  /**
   * FOXML repersention of the Fedora Object identified by $pid.
   *
   * Access through the function AjaxHandler::getFoxmlDocument().
   * Do not access directly as it may not exist.
   *
   * @var DOMDocument
   */
  protected $foxml;
  /**
   * XPath for the FOXML document identified by $foxml.
   *
   * Access through the function AjaxHandler::getFoxmlXPath().
   * Do not directly as it may not exist.
   *
   * @var DOMDocument
   */
  protected $xpath;
  /**
   *
   * @var <type>
   */
  protected $metadata;
  /**
   *
   * @var <type>
   */
  protected $metadataPath;
  protected $solr;

  /**
   *
   * @param string $pid
   */
  public function __construct($pid) {
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');
    $this->pid = $pid;
    $this->item = new Fedora_Item($pid);
  }

  /**
   *
   * @param int $offset
   * @param int $limit
   * @param string $filter
   * @param string $search_type
   * @param string $search_text
   * @return array
   */
  public function getMembers($offset, $limit, $filter, $search_type, $search_text) {
    switch ($filter) {
      case 'collections':
        $data = $this->getMemberCollections();
        list($data, $count) = $this->refineSearch($data, $offset, $limit, $search_type, $search_text);
        break;
      case 'objects':
        $data = $this->getMemberObjects();
        list($data, $count) = $this->refineSearch($data, $offset, $limit, $search_type, $search_text);
        break;
      case 'all':
      default:
        $data = $this->getAllMembers();
        list($data, $count) = $this->refineSearch($data, $offset, $limit, $search_type, $search_text);
        break;
    }
    return array('success' => true, 'data' => $data, 'total' => $count);
  }

  /**
   *
   * @return array
   */
  private function getAllMembers() {
    $query = 'select $object $title $content from <#ri>
                             where ($object <dc:title> $title
                             and $object <fedora-model:hasModel> $content
                             and ($object <fedora-rels-ext:isMemberOfCollection> <info:fedora/' . $this->pid . '>
                             or $object <fedora-rels-ext:isMemberOf> <info:fedora/' . $this->pid . '>)
                             and $object <fedora-model:state> <info:fedora/fedora-system:def/model#Active>)
                             minus $content <mulgara:is> <info:fedora/fedora-system:FedoraObject-3.0>
                             order by $title';
    return $this->query($query, $offset, $limit);
  }

  /**
   *
   * @return array
   */
  private function getMemberObjects() {
    $query = 'select $object $title $content from <#ri>
                             where ($object <dc:title> $title
                             and $object <fedora-model:hasModel> $content
                             and ($content <fedora-model:hasModel> <info:fedora/fedora-system:ContentModel-3.0>)
                             and ($object <fedora-rels-ext:isMemberOfCollection> <info:fedora/' . $this->pid . '>
                             or $object <fedora-rels-ext:isMemberOf> <info:fedora/' . $this->pid . '>)
                             and $object <fedora-model:state> <info:fedora/fedora-system:def/model#Active>)
                             minus $content <mulgara:is> <info:fedora/fedora-system:FedoraObject-3.0>
                             order by $title';
    return $this->query($query, $offset, $limit);
  }

  /**
   *
   * @return array
   */
  private function getMemberCollections() {
    $query = 'select $object $title $content from <#ri>
                             where ($object <dc:title> $title
                             and $object <fedora-model:hasModel> $content
                             and ($content <fedora-model:hasModel> <info:fedora/islandora:collectionCModel>)
                             and ($object <fedora-rels-ext:isMemberOfCollection> <info:fedora/' . $this->pid . '>
                             or $object <fedora-rels-ext:isMemberOf> <info:fedora/' . $this->pid . '>)
                             and $object <fedora-model:state> <info:fedora/fedora-system:def/model#Active>)
                             minus $content <mulgara:is> <info:fedora/fedora-system:FedoraObject-3.0>
                             order by $title';
    return $this->query($query, $offset, $limit);
  }

  private function query($query, $offset, $limit) {
    global $base_url;
    module_load_include('inc', 'fedora_repository', 'CollectionClass');
    $collection_class = new CollectionClass();
    $results = $collection_class->getRelatedObjects($this->pid, $limit, $offset, $query);
    if ($results != ' ') {
      $doc = new DOMDocument();
      $doc->loadXML(trim($results));
      $path = new DOMXPath($doc);
      $path->registerNamespace('sparql', 'http://www.w3.org/2001/sw/DataAccess/rf1/result');
      $query_results = $path->query('//sparql:result');
      if ($query_results->length > 0) {
        $count = $query_results->length;
        $returns = array();
        for ($i = 0; $i < $count; $i++) {
          $result = $query_results->item($i);
          $title = $path->query('sparql:title', $result)->item(0)->textContent;
          $pid = substr($path->query('sparql:object/@uri', $result)->item(0)->value, 12); // 12 characteres in "info:fedora/"
          $description = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
          $url = "$base_url/fedora/repository/$pid";
          $img_url = "$base_url/fedora/repository/$pid/TN";
          $returns[] = array('title' => $title, 'pid' => $pid, 'description' => $description, 'url' => $url, 'img_url' => $img_url);
        }
        return $returns;
      }
    }
    return array();
  }

  private function refineSearch($data, $offset, $limit, $search_type, $search_text) {
    if(isset($search_text) && trim($search_text) != '') {
      switch ($search_type) {
        case 'start':
          $data = array_filter($data, function ($item) use ($search_text) { return preg_match("/$search_text*/i", $item['title']) != 0; });
          break;
        case 'contains':
        default:
          $data = array_filter($data, function ($item) use ($search_text) { return preg_match("/.*$search_text.*/i", $item['title']) != 0; });
          break;
      }
      $count = count($data);
      $data = array_slice($data, $offset, $limit);
      return array($data, $count);
    }
    else {
      $count = count($data);
      $data = array_slice($data, $offset, $limit);
      return array($data, $count);
    }
  }

  private function count($query) {
    module_load_include('inc', 'fedora_repository', 'CollectionClass');
    $collection_class = new CollectionClass();
    $results = $collection_class->getRelatedObjects($this->pid, $limit, $offset, $query);
    if ($results != ' ') {
      $doc = new DOMDocument();
      $doc->loadXML(trim($results));
      $path = new DOMXPath($doc);
      $path->registerNamespace('sparql', 'http://www.w3.org/2001/sw/DataAccess/rf1/result');
      return $path->evaluate('count(//sparql:result)');
    }
    return 0;
  }

  private function getSolr() {
    if (empty($this->solr)) {
      module_load_include('php', 'islandora_solr_search', 'Solr/Service');
      $host = variable_get('islandora_solr_search_block_host', 'localhost');
      $port = variable_get('islandora_solr_search_block_port', '8080');
      $app_name = variable_get('islandora_solr_search_block_app_name', 'solr');
      $this->solr = new Apache_Solr_Service($host, $port, '/' . $app_name . '/');
    }
    return $this->solr;
  }

  public function querySolr($query) {
    $additional_params = array(
      'facet' => 'false',
      'qt' => variable_get("islandora_solr_search_block_request_handler", t("standard"))
    );
    $solr = $this->getSolr();
    $query = $string = trim(strtolower($query));
    $query = $solr->escape($query);
    try {
      $results = $solr->search($query, 0, 10, $additional_params);
    } catch (Exception $e) {
      drupal_set_message(t('error searching ') . $e->getMessage());
    }
    if (empty($results)) {
      drupal_set_message(t('Error searching solr index. Is the solr search block configured properly?'), 'error');
      return ' ';
    }
    var_dump($results);
  }

  /**
   * Get the label of this collection.
   * 
   * @return string
   */
  public function getLabel() {
    return $this->item->objectProfile->objLabel;
  }

  /**
   * Get the description of this collection.
   *
   * @return string
   */
  public function getDescription() {
    if ($this->hasMetadata()) {
      $xpath = $this->getMetadataXPath();
      $results = $xpath->query('/mods:mods/mods:abstract');
      if ($results && $results->length > 0) {
        return $results->item(0)->textContent;
      }
    }
    return NULL;
  }

  /**
   * Returns true if this collection has metadata.
   *
   * @return boolean
   */
  public function hasMetadata() {
    if (isset($this->metadata)) {
      return true;
    }
    return isset($this->item->datastreams['MODS']);
  }

  /**
   *
   * @return DOMDocument
   */
  private function &getMetadata() {
    if (empty($this->metadata)) {
      $mods = $this->item->get_datastream_dissemination('MODS');
      $this->metadata = new DOMDocument();
      $this->metadata->loadXML($mods);
    }
    return $this->metadata;
  }

  /**
   * 
   */
  private function getMetadataXPath() {
    if (empty($this->metadataPath)) {
      $doc = &$this->getMetadata();
      $this->metadataPath = new DOMXPath($doc);
      $this->registerNamespaces($doc->saveXML(), $this->metadataPath);
      $this->metadataPath->registerNamespace('mods', 'http://www.loc.gov/mods/v3');
    }
    return $this->metadataPath;
  }

  /**
   * Gets this objects FOXML repersentation, as a DOMDocument.
   *
   * Creates a new DOMDocument object from this objects exported FOXML, storing it
   * as a member if it doesn't already exist.
   *
   * @return DOMDocument
   */
  private function getFoxmlDocument() {
    if (empty($this->foxml)) {
      $foxml = $this->item->export_as_foxml();
      $this->foxml = new DOMDocument();
      $this->foxml->loadXML($foxml);
      return $this->foxml;
    }
    else {
      return $this->foxml;
    }
  }

  /**
   * Get the XPath for this object FOXML repersentation.
   *
   * Creates a new DOMXPath object, storing it as a member if it doesn't already exist.
   *
   * @return DOMXPath
   *   XPath for this object FOXML repersentation.
   */
  private function getFoxmlXPath() {
    if (empty($this->xpath)) {
      $foxml = $this->getFoxmlDocument();
      $this->xpath = new DOMXPath($foxml);
      $this->registerNamespaces($foxml->saveXML(), $this->xpath);
      return $this->xpath;
    }
    else {
      return $this->xpath;
    }
  }

  /**
   * Registers all namespaces found in the foxml document.
   *
   * @param string $foxml
   *   XML string of the exported fedora objects foxml.
   */
  private function registerNamespaces($doc, &$path) {
    $simple = new SimpleXMLElement($doc);
    $names = $simple->getNamespaces(TRUE);
    foreach ($names as $prefix => $uri) {
      $path->registerNamespace($prefix, $uri);
    }
  }

}
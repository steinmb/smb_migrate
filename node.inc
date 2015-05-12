<?php
/**
 * @file node.inc
 * Base class for migrating nodes into Drupal.
 */

/**
 * Common mappings for the Drupal 6 node migration.
 */
abstract class SMBNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

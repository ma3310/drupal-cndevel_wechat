<?php
/**
 * @file
 * Administration page callbacks for the cnDevel WeChat module.
 * only be loaded before options / settings are configured.
 */

/**
 * Form builder.
 * Configure Service Account related options.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function cndevel_wechat_service_admin_settings() {

    $form['cndevel_wechat_service_content_encryption_method'] = array(
        '#title' => t('Contents Encryption Method'),
        '#description' => t('Select an encryption method which will be used when changing contents between server with WeChat apps.'),
        '#type' => 'radios',
        '#options' => array(
            t('None'),
            t('AES Encoding'),
        ),
        '#default_value' => variable_get('cndevel_wechat_service_content_encryption_method', 0) // Default to None
    );


    $form['#submit'][] = 'cndevel_wechat_service_admin_settings_submit';

    return system_settings_form($form);
}

/**
 * Form Validation
 * prevent invalid values are inputted.
 *
 * 此函数会被 drupal 根据命名规则自动调用
 *
 * @param $form
 * @param $form_state
 */
function cndevel_wechat_service_admin_settings_validate ($form, $form_state){

}

/**
 * Process WeChat - Service Account settings submission.
 *
 * 用户输入会自动被保存到 variables 表，通过 devel 模块可以访问和修改。
 */
function cndevel_wechat_service_admin_settings_submit($form, $form_state) {

}

/**
 * Form builder.
 * Configure Enterprise Account related options.
 *
 * @ingroup forms
 * @see system_settings_form().
 * @link http://qydev.weixin.qq.com/debug
 */
function cndevel_wechat_enterprise_admin_settings() {

    watchdog("cnDevel WeChat Module", "cndevel_wechat_enterprise_admin_settings()");

    $form['WeChatEnterpriseCorpID'] = array(
        '#title' => t('CorpID'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseCorpID', ''), // 取不到变量时使用空字符串
                                                                        // checkboxes 值会是 array
    );
    $form['WeChatEnterpriseSecret'] = array(
        '#title' => t('Secret'),
        '#description' => t('Get this information from privilege management sub-page of settings page.<br>
Application has to be put in non-SystemAdmin group first, then use Secret of that group.'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseSecret', ''),
    );
    $form['WeChatEnterpriseAppID'] = array(
        '#title' => t('AppID'),
        '#type' => 'textfield',
        '#size' => 10,
        '#default_value' => variable_get('WeChatEnterpriseAppID', ''),
    );
    $form['WeChatEnterpriseToken'] = array(
        '#title' => t('Token'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseToken', ''),
    );
    $form['WeChatEnterpriseEncodingAESKey'] = array(
        '#title' => t('EncodingAESKey'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseEncodingAESKey', ''),
    );

    $form['#submit'][] = 'cndevel_wechat_enterprise_admin_settings_submit';

    return system_settings_form($form);
}

/**
 * prevent invalid values are inputted.
 *
 * @param $form
 * @param $form_state
 */
function cndevel_wechat_enterprise_admin_settings_validate ($form, $form_state){
    watchdog("cnDevel WeChat Module", "cndevel_wechat_enterprise_admin_settings_validate()");

    // AppID 应为正整数
    $value = $form_state['values']['WeChatEnterpriseAppID'];
    if (!is_numeric($value) || $value < 0){
        form_set_error('WeChatEnterpriseAppID', t('AppID should be a positive number.'));
    }
}


function cndevel_wechat_enterprise_admin_settings_submit ($form, $form_state){
    if ( !empty($form_state['values']['WeChatEnterpriseCorpID']) ){

    }
    if ( !empty($form_state['values']['WeChatEnterpriseSecret']) ){

    }
    if ( !empty($form_state['values']['WeChatEnterpriseAppID']) ){
        watchdog("cnDevel WeChat Module", "WeChatEnterpriseAppID: %value", array('%value'=>$form_state['values']['WeChatEnterpriseAppID']));

    }
    if ( !empty($form_state['values']['WeChatEnterpriseToken']) ){

    }
    if ( !empty($form_state['values']['WeChatEnterpriseEncodingAESKey']) ){

    }
}

